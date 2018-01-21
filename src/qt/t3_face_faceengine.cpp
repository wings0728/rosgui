#include <QSqlDatabase>
#include "../../include/rosgui/qt/t3_face_faceengine.hpp"


FaceEngine::FaceEngine()
{
    _doFRFrameCount = 0;
    _bReady = false;
    _threshold = 0.5f;

    _faceNum_ = 0;
    for(int k=0;k<MAX_FT_FACE;k++){
        _faceID_[k] = -1;
    }

    _uniqueIncID_ = 0;

    int ftWorkmemSize_ = 20 * 1024 * 1024;
    _FTWorkMem = new unsigned char[ftWorkmemSize_];
    int frWorkmemSize = 40 * 1024 * 1024;
    _FRWorkMem = new unsigned char[frWorkmemSize];


    int ret = AFT_FSDK_InitialFaceEngine((MPChar)APPID, (MPChar)FT_SDKKEY, _FTWorkMem, ftWorkmemSize_, &_hFTEngine, AFT_FSDK_OPF_0_HIGHER_EXT, 16, MAX_FT_FACE);
    if(ret != 0){

        return;
    }
    ret = AFR_FSDK_InitialEngine((MPChar)APPID, (MPChar)FR_SDKKEY, _FRWorkMem, frWorkmemSize, &_hFREngine);
    if(ret != 0){

        return;
    }

    _bReady = true;
}
FaceEngine::~FaceEngine()
{
    if(_hFTEngine)
    {
        AFT_FSDK_UninitialFaceEngine(_hFTEngine);
    }
    if(_hFREngine)
    {
        AFR_FSDK_UninitialEngine(_hFREngine);
    }

    if(_FTWorkMem)
    {
        delete[] _FTWorkMem;

    }
    if(_FRWorkMem)
    {
        delete[] _FRWorkMem;

    }
}

int FaceEngine::getFaceFeatureFromImage(QImage image,AFR_FSDK_FACEMODEL
                                        *_faceModels)
{

    int height_ = image.height();
    int width_ = image.width();

    unsigned char *frameData_ = new unsigned char [height_*width_*3];
    int frameFromat_ = ASVL_PAF_RGB24_B8G8R8;
    int pixelIndex_ = 0;
    for(int i =0 ;i<width_;i++)
    {
        for(int j = 0;j<height_;j++)
        {
            QColor color_ = image.pixel(i,j);
            //QColor color_ = image.pixelColor(i,j);
            *(frameData_ + pixelIndex_) = color_.blue();
            *(frameData_ + pixelIndex_ + 1) = color_.green();
            *(frameData_ + pixelIndex_ + 2) = color_.red();
            pixelIndex_ += 3;
        }
    }
    ASVLOFFSCREEN inputImg_ = { 0 };
    inputImg_.i32Height = width_;
    inputImg_.i32Width = height_;
    inputImg_.pi32Pitch[0] = height_*3;
    inputImg_.ppu8Plane[0] = frameData_;
    inputImg_.u32PixelArrayFormat = frameFromat_;
    LPAFT_FSDK_FACERES faceResult_ ;
    int ret = AFT_FSDK_FaceFeatureDetect(_hFTEngine,&inputImg_,&faceResult_);


    AFR_FSDK_FACEINPUT faceInput_;
    faceInput_.lOrient = faceResult_->lfaceOrient;
    faceInput_.rcFace.left = faceResult_->rcFace->left;
    faceInput_.rcFace.bottom = faceResult_->rcFace->bottom;
    faceInput_.rcFace.right = faceResult_->rcFace->right;
    faceInput_.rcFace.top = faceResult_->rcFace->top;
    AFR_FSDK_ExtractFRFeature(_hFREngine,&inputImg_,&faceInput_,_faceModels);
    qDebug() << _faceModels->lFeatureSize;
    _targetFaceModels = _faceModels;
    facePairMatch();
    if(faceResult_->nFace == 1)
    {
        return 1;
    }else
    {
        return 0;
    }
}

int FaceEngine::facePairMatch()
{
    QSqlDatabase database_ = QSqlDatabase::database(kDatabaseEngine);
    QSqlQuery query_(database_);

    query_.exec("select id,feature from T3Face where state >-1");
    float fScore_ = 0.0f;
    float scoreMax_ = 0.0f;
    int idMax_ = -1;
    int id_ = -1 ;
    AFR_FSDK_FACEMODEL localFaceModels_ = {0};
    QByteArray feature_;
    while(query_.next())
    {
        id_ = query_.value(0).toInt();
        feature_ = query_.value(1).toByteArray();
        localFaceModels_.lFeatureSize = feature_.size();
        localFaceModels_.pbFeature = new MByte[localFaceModels_.lFeatureSize];
        memcpy(localFaceModels_.pbFeature, feature_.data(), feature_.size());
        AFR_FSDK_FacePairMatching(_hFREngine,_targetFaceModels,&localFaceModels_,&fScore_);

        if (fScore_ > scoreMax_)
        {
            scoreMax_ = fScore_;
            idMax_ = id_;
        }
    }
    if(scoreMax_ != -1&& scoreMax_ > kThreshold )
    {


        query_.prepare("update T3Face set state = -3 where id = ?");
        //query_.prepare("delete from T3Face where id = ?");
        query_.bindValue(0,idMax_);
        if(query_.exec())
        {
            emit deleteFaceInfoById(idMax_);
        }

    }
}

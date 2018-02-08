#include "../../include/rosgui/qt/t3_face_network.hpp"

T3_Face_Network::T3_Face_Network()
{
    _server = new QTcpServer(this);
    _server->listen(QHostAddress::Any,kServerPost);
    connect(_server,&QTcpServer::newConnection,this,&T3_Face_Network::getSocket);
    _decoder_ = Decoder::getDecoder();
    _decoder_->initDecoder();
    _frameLineData_ = new FrameLineData();
    _udpSocket = new QUdpSocket(this);
    _node = rosgui::QNode::getInstance();
    _udpSocket->bind(8888,QUdpSocket::ShareAddress);
    _videoTimer = new QTimer();
    _getVideotimer = new QTimer();
    _sendTimer = new QTimer();
    _heartBeatNetwork = new QTimer();
    connect(_getVideotimer,&QTimer::timeout,this,&T3_Face_Network::reGetTheVideo);
    connect(_udpSocket,&QUdpSocket::readyRead,this,&T3_Face_Network::processUDPData);
    connect(_decoder_,&Decoder::newFrame,this,&T3_Face_Network::stopVideoTimer);
    connect(_videoTimer,&QTimer::timeout,this,&T3_Face_Network::resendTheVideo);
    connect(_node,&rosgui::QNode::lowPower,this,&T3_Face_Network::sendLowPowerSingle);
    connect(_sendTimer,&QTimer::timeout,this,&T3_Face_Network::sendMessage);
    connect(_heartBeatNetwork,&QTimer::timeout,this,&T3_Face_Network::HeartBeat);
    qDebug() << "network init";

}
T3_Face_Network::~T3_Face_Network()
{
  delete _decoder_;
  delete _frameLineData_;
}
T3_Face_Network* T3_Face_Network::getT3FaceNetwork()
{
  static T3_Face_Network network;
  return &network;
}

void T3_Face_Network::getSocket()
{
    qDebug() << "network t3_face_network 41";
    _socket = _server->nextPendingConnection();
    _isNetworkConnected_ = true;
    connect(_socket,&QTcpSocket::readyRead,this,&T3_Face_Network::analyzeNetworkData);
    connect(_socket,&QTcpSocket::disconnected,this,&T3_Face_Network::socketDisconnected);
    _decoder_->initDecoder();
    if(!_heartBeatNetwork->isActive())
    {
      _heartBeatNetwork->start(30000);
    }

    getVideo();

}

void T3_Face_Network::analyzeNetworkData()
{
    qDebug() << "read the data";
    QDataStream stream_(_socket) ;
    stream_.setVersion(QDataStream::Qt_5_5);

    stream_ >> _blockSize;
    qDebug() << _blockSize;
    stream_ >> _readSign;
    qDebug() << _readSign;
    switch(_readSign)
    {
        case 1:
            readFrameData();
        break;
        case 2:
            stream_ >> _id;
            qDebug() << _id;
            getLog(_id);
            _blockSize = 0;
        break;

    }





}

void T3_Face_Network::readFrameData()
{

    QByteArray buf;
    quint32 lenght = _networkDataBuffer.size();
    if(_networkDataBuffer.size() <_blockSize)
    {
        return ;
    }
    if(_networkDataBuffer.size() >= _blockSize)
    {
        QDataStream stream_(&_networkDataBuffer,QIODevice::ReadOnly);

        quint32 a;
        stream_  >> a;
        stream_  >> a;


        stream_ >> _personNum;
        //qDebug() << _personNum;
        _frameLineData_->personNum = _personNum;
        for(int i =0 ; i<_personNum; i++)
        {

            stream_ >> _id;
            stream_ >> _left;
            stream_ >> _right;
            stream_ >> _top;
            stream_ >> _bottom;
            stream_ >> _dot1;
            stream_ >> _dot2;

            if(_idList.size() <= _personNum)
            {
                _frameLineData_->idList << _id;
                _frameLineData_->leftList << _left;
                _frameLineData_->rightList << _right;
                _frameLineData_->topList << _top;
                _frameLineData_->bottomList << _bottom;
                _frameLineData_->dot1List << _dot1;
                _frameLineData_->dot2List << _dot2;
            }

            _frameLineData_->idList.replace(i,_id);
            _frameLineData_->leftList.replace(i,_left);
            _frameLineData_->rightList.replace(i,_right);
            _frameLineData_->bottomList.replace(i,_bottom);
            _frameLineData_->topList.replace(i,_top);
            _frameLineData_->dot1List.replace(i,_dot1);
            _frameLineData_->dot2List.replace(i,_dot2);

        }
        //stream_ >> _frameData;
        QString datetime_;
        stream_ >> datetime_;
        //qDebug() << datetime_;
        QString dataTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //qDebug() <<  dataTimeString;
        //_decoder_->decoderFrame(_frameData.data(),_frameData.size());
        buf = _networkDataBuffer.right(lenght - _blockSize);
        _networkDataBuffer = buf;
        _blockSize = 0;
        _readSign = 0;

    }

}

void T3_Face_Network::socketDisconnected()
{
    _isNetworkConnected_ = false;
    emit networkDisconnect();

}

void T3_Face_Network::getVideo()
{
    _sign = 2;
    QByteArray block_;
    QDataStream stream_(&block_,QIODevice::WriteOnly);
    stream_.setVersion(QDataStream::Qt_5_5);
    stream_ << (quint32)sizeof(quint32);
    stream_ << (quint32)_sign;
    _socket->write(block_);
    qDebug() << "get video";


}

void T3_Face_Network::closeVideo()
{
  _sign = 3;
  QByteArray block_;
  QDataStream stream_(&block_,QIODevice::WriteOnly);
  stream_.setVersion(QDataStream::Qt_5_5);
  stream_ << (quint32)sizeof(quint32);
  stream_ << (quint32)_sign;
  _socket->write(block_);
}

void T3_Face_Network::updateClientDataBase()
{
    _sendTimer->start(5000);
    _sendSign = 1;

}

void T3_Face_Network::sendTTS(int sign, QString string)
{
    _sign = kSendSignTTS;
    QByteArray block_ ;
    QDataStream stream_(&block_,QIODevice::WriteOnly);
    stream_.setVersion(QDataStream::Qt_5_5);
    stream_ << (quint32)sizeof(quint32);
    stream_ << (quint32)_sign ;
    stream_ << (int)sign;
    stream_ << string;
    _socket->write(block_);
}

void T3_Face_Network::processUDPData()
{
    if(!_videoTimer->isActive())
    {
      _videoTimer->start(4000);
    }

    while(_udpSocket->hasPendingDatagrams())
    {
        QByteArray data;

        data.resize(_udpSocket->pendingDatagramSize());
        _udpSocket->readDatagram(data.data(),data.size());
        readTheUDPData(data);
        //_decoder_->decoderFrame(data.data(),data.size());

    }
}

void T3_Face_Network::sendDeteleFaceInfoById(int id)
{
   _sendTimer->start(5000);
   _sendID = id;
   _sendSign = 4;
}

void T3_Face_Network::sendLowPowerSingle()
{
  _sign = kLowPower;
  QByteArray block_ ;
  QDataStream stream_(&block_,QIODevice::WriteOnly);
  stream_.setVersion(QDataStream::Qt_5_5);
  stream_ << (quint32)sizeof(quint32);
  stream_ << (quint32)_sign ;
  _socket->write(block_);
}

void T3_Face_Network::stopVideoTimer()
{
  _videoTimer->stop();
  _isNetworkConnected_ = true;
}

void T3_Face_Network::resendTheVideo()
{
  _videoTimer->stop();
  closeVideo();
  _decoder_->initDecoder();
  _getVideotimer->start(1000);

}

void T3_Face_Network::reGetTheVideo()
{
  _getVideotimer->stop();
  getVideo();
}

void T3_Face_Network::readTheUDPData(QByteArray data)
{

  if(true)
  {
      QDataStream stream_(&data,QIODevice::ReadOnly);
     quint32 size_ = 0;
     stream_ >> size_;
      stream_ >> _frameData;
      stream_ >> _personNum;
      _frameLineData_->personNum = _personNum;
      for(int i =0 ; i<_personNum; i++)
      {

          stream_ >> _id;
          stream_ >> _left;
          stream_ >> _right;
          stream_ >> _top;
          stream_ >> _bottom;
          stream_ >> _dot1;
          stream_ >> _dot2;

          if(_idList.size() <= _personNum)
          {
              _frameLineData_->idList << _id;
              _frameLineData_->leftList << _left;
              _frameLineData_->rightList << _right;
              _frameLineData_->topList << _top;
              _frameLineData_->bottomList << _bottom;
              _frameLineData_->dot1List << _dot1;
              _frameLineData_->dot2List << _dot2;
          }

          _frameLineData_->idList.replace(i,_id);
          _frameLineData_->leftList.replace(i,_left);
          _frameLineData_->rightList.replace(i,_right);
          _frameLineData_->bottomList.replace(i,_bottom);
          _frameLineData_->topList.replace(i,_top);
          _frameLineData_->dot1List.replace(i,_dot1);
          _frameLineData_->dot2List.replace(i,_dot2);

      }

      QString datetime_;
      stream_ >> datetime_;
      _decoder_->decoderFrame(_frameData.data(),_frameData.size());
  }
}

void T3_Face_Network::sendMessage()
{
  if(_sendSign == 1)
  {
    _sign = 1;
    _sendTimer->stop();
    QByteArray block_ ;
    QDataStream stream_(&block_,QIODevice::WriteOnly);
    stream_.setVersion(QDataStream::Qt_5_5);
    stream_ << (quint32)sizeof(quint32);
    stream_ << (quint32)_sign ;
    _socket->write(block_);

    qDebug() << "newFace";
  }
  if(_sendSign == 4)
  {
    _sign = 4;
    _sendTimer->stop();
    QByteArray block_ ;
    QDataStream stream_(&block_,QIODevice::WriteOnly);
    stream_.setVersion(QDataStream::Qt_5_5);
    stream_ << (quint32)sizeof(quint32);
    stream_ << (quint32)_sign ;
    stream_ << (quint32)_sendID ;
    _socket->write(block_);
    qDebug() << "deleteface";

  }



}


void T3_Face_Network::HeartBeat()
{
  _sign = 10;
  QByteArray block_ ;
  QDataStream stream_(&block_,QIODevice::WriteOnly);
  stream_.setVersion(QDataStream::Qt_5_5);
  stream_ << (quint32)sizeof(quint32);
  stream_ << (quint32)_sign ;
  _socket->write(block_);
  qDebug() << "hearBeat";
}

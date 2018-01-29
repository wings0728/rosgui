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
    _udpSocket->bind(8888,QUdpSocket::ShareAddress);
    _videoTimer = new QTimer();
    _getVideotimer = new QTimer();
    connect(_getVideotimer,&QTimer::timeout,this,&T3_Face_Network::reGetTheVideo);
    connect(_udpSocket,&QUdpSocket::readyRead,this,&T3_Face_Network::processUDPData);
    connect(_decoder_,&Decoder::newFrame,this,&T3_Face_Network::stopVideoTimer);
    connect(_videoTimer,&QTimer::timeout,this,&T3_Face_Network::resendTheVideo);
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
    qDebug() << "network";
    _socket = _server->nextPendingConnection();
    _isNetworkConnected_ = true;
    connect(_socket,&QTcpSocket::readyRead,this,&T3_Face_Network::analyzeNetworkData);
    connect(_socket,&QTcpSocket::disconnected,this,&T3_Face_Network::socketDisconnected);
    _decoder_->initDecoder();
    getVideo();
}

void T3_Face_Network::analyzeNetworkData()
{

    _networkDataBuffer.append(_socket->readAll());
    QDataStream stream_(&_networkDataBuffer,QIODevice::ReadOnly) ;
    stream_.setVersion(QDataStream::Qt_5_5);
    if(0 == _blockSize)
    {
        stream_ >> _blockSize;
        stream_ >> _readSign;

        switch(_readSign)
        {
            case 1:
                readFrameData();
            break;
            case 2:
                stream_ >> _id;
                getLog(_id);
            break;

        }
    }else
    {
      switch(_readSign)
      {
          case 1:
              readFrameData();
          break;
          case 2:
              stream_ >> _id;
              emit getLog(_id);
          break;
      }

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
    _sign = 1;
    QByteArray block_ ;
    QDataStream stream_(&block_,QIODevice::WriteOnly);
    stream_.setVersion(QDataStream::Qt_5_5);
    stream_ << (quint32)sizeof(quint32);
    stream_ << (quint32)_sign ;
    _socket->write(block_);

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
        qDebug() << data.size();
        readTheUDPData(data);
        //_decoder_->decoderFrame(data.data(),data.size());
    }
}

void T3_Face_Network::sendDeteleFaceInfoById(int id)
{
    _sign = 4;
    QByteArray block_ ;
    QDataStream stream_(&block_,QIODevice::WriteOnly);
    stream_.setVersion(QDataStream::Qt_5_5);
    stream_ << (quint32)sizeof(quint32);
    stream_ << (quint32)_sign ;
    stream_ << (quint32)id;
    _socket->write(block_);
}

void T3_Face_Network::stopVideoTimer()
{
  _videoTimer->stop();
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
     qDebug() << size_;
      stream_ >> _frameData;

      stream_ >> _personNum;
      qDebug() << _personNum;
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
      qDebug() << datetime_;
      QString dataTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
      qDebug() <<  dataTimeString;
      _decoder_->decoderFrame(_frameData.data(),_frameData.size());
  }
}

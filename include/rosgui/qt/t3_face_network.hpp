#ifndef T3_FACE_NETWORK_H
#define T3_FACE_NETWORK_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTimer>
#include "t3_af_config.hpp"
#include "t3_library.hpp"
#include "t3_face_decoder.hpp"
#include "../ros/qnode.hpp"


class FrameLineData
{
public :
  int personNum ;
  QList<quint32> rightList;
  QList<quint32> leftList;
  QList<quint32> topList;
  QList<quint32> bottomList;
  QList<quint32> dot1List;
  QList<quint32> dot2List;
  QList<int> idList;
};
class T3_Face_Network : public QObject
{
    Q_OBJECT
public:
    static T3_Face_Network* getT3FaceNetwork();

    ~T3_Face_Network();

    void closeVideo();
    void sendTTS(int sign, QString string);
    bool _isNetworkConnected_ = false;
    Decoder *_decoder_;
    FrameLineData *_frameLineData_;
    void updateClientDataBase();
    void sendDeteleFaceInfoById(int id);
    void getVideo();

private:
    T3_Face_Network();
    void readTheUDPData(QByteArray data);
    QTcpServer *_server;
    QTcpSocket *_socket;
    QByteArray _networkDataBuffer;//
    QByteArray _frameData;
    QUdpSocket *_udpSocket;
    rosgui::QNode *_node;

    quint32 _blockSize = 0;
    quint32 _readSign = 0;//读数据标识符 ,1表示传过来的数据为帧数据,2表示传过来的数据为新注册的用户数据.
    quint32 _personNum = 0;
    quint32 _right = 0;
    QList<quint32> _rightList;
    quint32 _left = 0;
    QList<quint32> _leftList;
    quint32 _top = 0;
    QList<quint32>_topList;
    quint32 _bottom = 0;
    QList<quint32> _bottomList;
    quint32 _dot1 = 0;
    QList<quint32> _dot1List;
    quint32 _dot2 = 0;
    QList<quint32> _dot2List;
    int _id = 0;
    QList<int> _idList;
    quint8 _sign = 0;//写数据标识位,用来发送命令,1表示更新数据库,2表示请求视频数据,3用来停止视频传输.
    //quint32 _id;
    QTimer *_videoTimer;
    QTimer *_getVideotimer;
    QTimer *_sendTimer;
    QTimer *_heartBeatNetwork;
    int _sendSign ;
    int _sendID;
    void readFrameData();
    void processUDPData();



private slots:
    void getSocket();
    void analyzeNetworkData();
    void socketDisconnected();
    void stopVideoTimer();
    void resendTheVideo();
    void reGetTheVideo();
    void sendLowPowerSingle();
    void sendMessage();
     void HeartBeat();

signals:
    void getLog(int id);
    void networkDisconnect();
};

#endif // T3_FACE_NETWORK_H

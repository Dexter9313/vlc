#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QElapsedTimer>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class QtVLCWidget : public QOpenGLWindow
{
    Q_OBJECT

public:
    QtVLCWidget(QWidget *parent = 0);
    ~QtVLCWidget();

    bool playMedia(const char* url);

signals:
    void contextReady(QOpenGLContext *ctx);

public slots:
    void cleanup();

protected:
	void keyPressEvent(QKeyEvent* e) override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    QOpenGLVertexArrayObject m_vao;
    std::unique_ptr<QOpenGLShaderProgram> m_program;

    std::unique_ptr<class VLCVideo> mVLC;

    void stop();
    struct libvlc_instance_t*  m_vlc = nullptr;
    struct libvlc_media_player_t* m_mp = nullptr;
    struct libvlc_media_t* m_media = nullptr;

    QOpenGLBuffer vertexBuffer, vertexIndexBuffer;

	QElapsedTimer timer;
};

#endif /* GLWIDGET_H */

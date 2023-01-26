#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QMainWindow>

#ifdef QT_STATIC
# include <QtPlugin>
# ifdef _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
# endif
#endif


#include "qtvlcwidget.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // this important so we can call makeCurrent from our rendering thread
    QCoreApplication::setAttribute(Qt::AA_DontCheckOpenGLContextThreadAffinity);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(fmt);

    QtVLCWidget *glWidget = new QtVLCWidget;
	glWidget->show();

    glWidget->playMedia(argv[1]);

	QTimer t;
	t.setInterval(0);
	QObject::connect(&t, &QTimer::timeout, [glWidget](){glWidget->update(); });
	t.start();


    return app.exec();
}

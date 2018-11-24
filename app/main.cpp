#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QStandardPaths>

#ifdef Q_OS_ANDROID
	#include <QtAndroid>
	#include <QAndroidJniEnvironment>
#endif



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
	bool result = QFile::copy(":/sounds/track1.mp3", tempDir + "/track1.mp3" ); // must be copied to be seekable
	app.setOrganizationName("tarmo-qt");
    app.setOrganizationDomain("tarmo-qt.com");
    app.setApplicationName("mysterium-app");

#ifdef Q_OS_ANDROID
	//keep screen on:
	QAndroidJniObject activity = QtAndroid::androidActivity();
	if (activity.isValid()) {
		QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");

		if (window.isValid()) {
			const int FLAG_KEEP_SCREEN_ON = 128;
			window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
		}
		QAndroidJniEnvironment env; if (env->ExceptionCheck()) { env->ExceptionClear(); } //Clear any possible pending exceptions.
	}
#endif


    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

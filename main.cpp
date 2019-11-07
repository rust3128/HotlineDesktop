#include "mainwindow.h"

#include "LoggingCategories/loggingcategories.h"
#include "DataBase/database.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QTranslator>
#include <QLibraryInfo>
#include <QSplashScreen>


// Умный указатель на файл логирования
static QScopedPointer<QFile>   m_logFile;

// Объявление обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet("QToolTip{background-color: rgb(255,255,255); border: 2px solid darkkhaki; padding: 5px; border-radius: 1px; }");

    // Устанавливаем файл логирования
    m_logFile.reset(new QFile("HotlineDesktop.log"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);
    qInfo(logInfo()) << "Запуск программы.";

#ifndef QT_NO_TRANSLATION
    //Определяем имя языкового файла в зависимости от текущей локали
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    //Создаем и пытаемся загрузить
    QTranslator *translator = new QTranslator(&a);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translator);
    else
        qWarning(logWarning()) << "Не удалось загрузить языковый файл.";
#endif

    DataBase *db = new DataBase();
    if(!db->connectDB()){
        qCritical(logCritical()) << "Аварийное завершение работы.";
        return 1;
    }

//    if(!db->connectCenralDB()){
//        qInfo(logInfo()) << "Завершение работы. Не удалось подключится к центральной базе.";
//        return 1;
//    }

    MainWindow w;
    w.show();

    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    QTextStream console(stdout);
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
#ifdef QT_DEBUG
    case QtInfoMsg:
        out << "[INF] ";
        console << "Info:     " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << endl;
        break;
    case QtDebugMsg:
        out << "[DBG] " ;
        console << "Debug:    " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << endl;
        break;
    case QtWarningMsg:
        out << "[WRN] ";
        console << "Warning:  " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] "  << endl;
        break;
    case QtCriticalMsg:
        out << "[CRT] ";
        console << "Critical: " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << endl;
        break;
    case QtFatalMsg:
        out << "[FTL] ";
        console << "Fatality: " << msg << " ***[" << context.function << " File: " << context.file << " Line: " << context.line << "] " << endl;
        break;
#else
    case QtInfoMsg:     out << "[INF] "; break;
    case QtDebugMsg:    out << "[DBG] "; break;
    case QtWarningMsg:  out << "[WRN] "; break;
    case QtCriticalMsg: out << "[CRT] "; break;
    case QtFatalMsg:    out << "[FTL] "; break;
#endif

    }

    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": " << msg;
    out << "  ***[" << context.function << " File: " << context.file << " Line: " << context.line << "]***" << endl;
    // Очищаем буферизированные данные
    out.flush();
    console.flush();
}

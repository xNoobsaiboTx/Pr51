#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <fileinfo.h>
#include <folderservice.h>
class Qwe37TestsTest : public QObject
{
    Q_OBJECT
    
public:
    Qwe37TestsTest();
    
private Q_SLOTS:

    void fileInfoConstructorTest();
    void fileInfoSetCommentTest();
    void SetCommentExceptionTest();
    void FolderServiceConstructorTets();
};

Qwe37TestsTest::Qwe37TestsTest()
{
}

void Qwe37TestsTest::FolderServiceConstructorTets()
{
    FolderService* fs=new FolderService("qwse");
    QCOMPARE(true,false);
}

void Qwe37TestsTest::SetCommentExceptionTest()
{
    fileInfo *fi = new fileInfo("qwe");
    bool ok=true;
    try
    {
        fi->SetComment("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
    }
    catch(char* str)
    {
        ok=false;
    }
    QCOMPARE(ok,false);
}

void Qwe37TestsTest::fileInfoConstructorTest()
{
    fileInfo *fi = new fileInfo("qwe");
    QCOMPARE(fi->GetPath(),QString("qwe"));
}

void Qwe37TestsTest::fileInfoSetCommentTest()
{
    fileInfo *fi = new fileInfo("qwe");
    fi->SetComment("comment");
    QCOMPARE(fi->GetComment(),QString("comment"));
}

QTEST_MAIN(Qwe37TestsTest)

#include "tst_qwe37teststest.moc"

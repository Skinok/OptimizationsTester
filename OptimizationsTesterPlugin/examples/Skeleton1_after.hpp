#include <QDebug>
#include <QList>
#include <QString>

int main()
{
    iNeedToBeOptimized();  
	return 0;
}

void iNeedToBeOptimized(){
    
    // Write code here
    qDebug() << "Hello World!";
    
    QList<QString> strings;
    for(int i = 0; i < 10000; i++)
    {
        // Stack allocation
        strings = QString("test");
    }   
}
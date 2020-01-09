#include "data_import.h"
#include "qoauth2test.h"

data_import::data_import(QObject *parent) : QObject(parent)
{

}
void data_import::set_token()
{
    QOAuth2Test *x = new QOAuth2Test();
    m_token = x->getToken();
    qDebug() << "GET OKKKKKKKK" << m_token;
}

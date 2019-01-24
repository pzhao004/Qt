#include "kbcontext.h"

//
KBContext::KBContext(QObject *parent) : QObject (parent)
{
    m_active=false;
    m_listIMs << "abc" << "123" << "arabic" << "turkish" << "cyrillic";
    m_idxIM = 0;
    m_curr1Str = "First  InputText";
    m_curr2Str = "Second InputText";

    //prepare data
    m_keyboardmodel = new KeyboardModel(this);
    updateKeyBoard();

    //Handle the functions keys,suchas backspace/ok
    connect(m_keyboardmodel,SIGNAL(enterKeyVal(int)),this,SLOT(sendKeyVal(int)));
    //Handle the non-function keys, q/a/s/b/c/d/1/2/3
    connect(m_keyboardmodel,SIGNAL(enterKeyChar(QChar)),this,SLOT(sendKeyChar(QChar)));
}
//
KBContext::~KBContext(){}
//
void KBContext::setOwner(QQmlApplicationEngine &engine){
    m_engine=&engine;
    if(!m_engine){
        qDebug() << "Owner can't be null";
    }
    QQmlContext * rootContext = m_engine->rootContext();
    rootContext->setContextProperty("KBCtx",this);
    rootContext->setContextProperty("KbdMode",m_keyboardmodel);
}
void KBContext::getTextInputFocus(){
    qDebug() <<"getTextInputFocus...";
    m_textInputFocus = m_engine->rootObjects()[0]->findChild<QObject*>(m_objectName);

}
//
QString KBContext::curr1Str() const
{
    return m_curr1Str;
}
//
QString KBContext::curr2Str() const{
    return m_curr2Str;
}
QString KBContext::obName() const{
    return m_objectName;
}
//
bool KBContext::active() const{
    return m_active;
}
//
QString KBContext::currIM() const{
    return m_listIMs.at(m_idxIM);
}
//
QString KBContext::nextIM() const
{
    int next = 0;
    if (m_idxIM + 1 < m_listIMs.size()) {
        next = (m_idxIM + 1);
    }
    return m_listIMs.at(next);
}
//
void KBContext::toggleIM(){
    if(m_idxIM+1<m_listIMs.size()){
        m_idxIM++;
    }else {
        m_idxIM =0;
    }

    emit currIMChanged(currIM());
    emit nextIMChanged(nextIM());
    updateKeyBoard();
}
//
void KBContext::doInput(const QString &objectName){
    m_objectName = objectName;
    emit obNameChanged(obName());

    m_active=true;
    emit activeChanged();

    //get the new object of text input
    getTextInputFocus();
}
//when virtual key mode changed, update the keyboard.
void KBContext::updateKeyBoard(){
    if(!m_keyboardmodel){
        return;
    }
    if(m_idxIM<m_listIMs.size()){
        m_keyboardmodel->setInputMode(m_listIMs.at(m_idxIM));
    }
}
//handle delete key
void KBContext::sendKeyVal(const int i){
    qDebug("kbdcontext::sendkeyvalue %d",i);
    if(i == Qt::Key_Backspace){
        if(m_objectName=="t1"){
            m_curr1Str.truncate(m_curr1Str.length()-1);
            emit curr1StrChanged(curr1Str());
        }else if(m_objectName =="t2"){
            m_curr2Str.truncate(m_curr2Str.length()-1);
            emit curr2StrChanged(curr2Str());
        }else{
        }
    }else if(i == Qt::Key_Enter){
        // handle the OK key
        m_active = false;
        emit activeChanged();

        // Input text lose the focus
        qDebug() <<"input text lose the focus...";
        m_textInputFocus->setProperty("focus",false);
    }
}
void KBContext::sendKeyChar(const QChar q){
    if(m_objectName == "t1"){
        m_curr1Str=m_curr1Str.append(q);
        emit curr1StrChanged(curr1Str());
    }else if(m_objectName=="t2"){
        m_curr2Str=m_curr2Str.append(q);
        emit curr2StrChanged(curr2Str());
    }else{}
}

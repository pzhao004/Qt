#include "kbcontext.h"

//
KBContext::KBContext(QObject *parent) : QObject (parent)
{
    m_active=false;
    m_listIMs << "abc" << "123" << "arabic" << "turkish" << "cyrillic";
    m_idxIM = 0;

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
    m_designBll = new DesignBLL();
    QQmlContext * rootContext = m_engine->rootContext();
    rootContext->setContextProperty("KBCtx",this);
    rootContext->setContextProperty("KbdMode",m_keyboardmodel);
    rootContext->setContextProperty("DesignBLL",m_designBll);
}
void KBContext::getTextInputFocus(){
    qDebug() <<"getTextInputFocus...." + m_objectName;
    QObject * root=nullptr;
    QList<QObject*> rootObjects = m_engine->rootObjects();
    int count = rootObjects.size();
    for(int i =0; i< count;i++){
        if(rootObjects.at(i)->objectName()=="rootObject"){
            root=rootObjects.at(i);
            break;
        }
    }

    m_textInputFocus = root->findChild<QObject*>(m_objectName);
    childrenOjbects = m_textInputFocus->findChildren<QObject*>();
    qDebug() << childrenOjbects;

    if(m_textInputFocus ==nullptr){
        qDebug() <<"object is null....";
    }
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
    qDebug() << "show the keyboard...";
    m_active=true;
    emit activeChanged();

    //get the new object of text input
    getTextInputFocus();
}
void KBContext::doInput(const int index){
    m_index = index;
     qDebug() << "show the keyboard..."<<index;

     m_active=true;
     emit activeChanged();
}
void KBContext::doInput(const int index,const QString &objectName){
    m_index = index;
    m_objectName = objectName;
     qDebug() << "show the keyboard..."<<index << "object:" << m_objectName;

     m_active=true;
     emit activeChanged();
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
    qDebug() <<"m_objectName is:" << m_objectName << "kbdcontext::sendkeyvalue is:" << i;
    if(i == Qt::Key_Backspace){
        if(m_objectName=="txi"){
            //here handle the detail string
            qDebug() << "index is :" << m_index <<  "input text object is: " << m_objectName;
            m_designBll->deleteChar(m_index);
        }else if(m_objectName=="txf"){
            qDebug() << "index is :" << m_index <<  "input text object is: " << m_objectName;
            m_designBll->deleteChar2(m_index);
        }else if(m_objectName =="t2"){
        }else{
        }
    }else if(i == Qt::Key_Enter){
        // handle the OK key
        m_active = false;
        emit activeChanged();
        // Input text lose the focus
        qDebug() << "input text lose the focus...";
        m_designBll->changeFocus(m_index);
    }
}
void KBContext::sendKeyChar(const QChar q){
    qDebug() << "add char is:" << q;
    if(m_objectName=="txi"){
        qDebug() << "handle the char...";
        m_designBll->addChar(m_index,q);
    }else if(m_objectName=="txf"){
        m_designBll->addChar2(m_index,q);
    }else{
        qDebug() << "null...";
    }
}

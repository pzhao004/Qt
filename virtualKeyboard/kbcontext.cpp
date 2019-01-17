#include "kbcontext.h"

KBContext::KBContext(QObject *parent) : QObject (parent)
{
    m_active=false;
    m_listIMs << "abc" << "123" << "pinyin" ;
    m_idxIM =0;

    //prepare data
    m_keyboardmodel = new KeyboardModel(this);
    updateKeyBoard();
}

KBContext::~KBContext(){}

void KBContext::setOwner(QQmlApplicationEngine &engine){
    m_engine=&engine;
    if(!m_engine){
        qDebug() << "Owner can't be null";
    }
    QQmlContext * rootContext = m_engine->rootContext();
    rootContext->setContextProperty("KBCtx",this);
    rootContext->setContextProperty("KbdMode",m_keyboardmodel);
}

QString KBContext::currStr() const
{
    return m_currStr;
}

bool KBContext::active() const{
    return m_active;
}

void KBContext::doInput(const QString &initStr){
    m_currStr =  initStr;
    emit currStrChanged(currStr());

    m_active=true;
    emit activeChanged();
}

void KBContext::updateKeyBoard(){
    if(!m_keyboardmodel){
        return;
    }
    if(m_idxIM<m_listIMs.size()){
        m_keyboardmodel->setInputMode(m_listIMs.at(m_idxIM));
    }
}

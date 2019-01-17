#include "keyboardmodel.h"

//
void MyKey::printOut(){
   qDebug() << "[KEY]:" << text << " seq=" << seq << "span=" << span;
}

KeyboardModel::KeyboardModel(QObject *parent) : QAbstractListModel(parent),
    m_keyCount(0)
{
    qDebug() << "KeyboardMode Enter Function.";
    m_roles[FIELD_ISEMPTY] = "isEmpty";
    m_roles[FIELD_ISICON] = "isIcon";
    m_roles[FIELD_ISFUNC] = "isFunc";
    m_roles[FIELD_TXT] = "txt";
    m_roles[FIELD_PIC] = "pic";
    m_roles[FIELD_SPAN] = "span";
    m_roles[FIELD_KEYCOLOR] = "keyColor";
}

KeyboardModel::~KeyboardModel(){

}

int KeyboardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_keyCount;
}

QVariant KeyboardModel::data(const QModelIndex &index, int role) const
{
    int r = index.row();
    int c = role - Qt::UserRole - 1;

    if (r < 0 || r >= m_keyCount || r >= m_vecKeys.size()
            || c < 0 || c >= m_roles.count()) {
        return QVariant();
    }

    MyKey* pKey = m_vecKeys.at(r);
    if (!pKey) {
        return QVariant();
    }

    switch (role) {
    case FIELD_ISEMPTY:
        return pKey->isEmtpy;
    case FIELD_ISICON:
        return pKey->isIcon;
    case FIELD_ISFUNC:
        return pKey->isFunc;
    case FIELD_TXT: // For text field need to format it
        return formatKeyText(pKey);
    case FIELD_PIC:
        return pKey->pic;
    case FIELD_SPAN:
        return pKey->span;
    case FIELD_KEYCOLOR:
        return pKey->keyColor;
    default:
        return QVariant();
    }
}
//
QHash<int, QByteArray> KeyboardModel::roleNames() const
{
    return m_roles;
}
// for UI showing
QString KeyboardModel::formatKeyText(MyKey *pKey) const
{
    if (!pKey) {
        return QString("");
    }

    if (pKey->isFunc) {
        // for function key, return the function name
        return pKey->func;
    }

    // special handling for Space key
    if (pKey->text == "Space") {
        return pKey->text;
    }

    // other alphabetic key
    if (m_isCapsLock) {
        return pKey->text.toUpper();
    } else {
        return pKey->text.toLower();
    }
}
//
void KeyboardModel::setInputMode(const QString &im){
    m_inputMode = im;
    emit inputModeChanged(inputMode());

    // adjust keyboard according to input mode
    QString fileName = "keyboard_latin.xml";
    if(im == "pinyin"){
        fileName= "keyboard_latin.xml";
    }else if(im.toLower()=="abc"){
        // determine caps-lock and shift status
        if (im == "abc") {
            m_isCapsLock = false;
        } else if (im == "Abc") {
            if (m_isShift) {
                 m_isCapsLock = true;
            } else {
                m_isCapsLock = false;
            }
        } else if (im == "ABC") {
            m_isCapsLock = true;
        }
    }else if (im == "uni" || im == "123" || im == "symbol") {
        fileName = "keyboard_123.xml";
    } else if (im == "turkish") {
        fileName = "keyboard_turkish.xml";
    } else if (im == "cyrillic") {
        fileName = "keyboard_cry.xml";
    } else if (im == "arabic") {
        fileName = "keyboard_arabic.xml";
    }
    loadKbd(fileName);
    m_currKbdFile = fileName;
}
//
QString KeyboardModel::kbdPath(){
    return QString(":/keyboard/");
}
//
void KeyboardModel::loadKbd(const QString &kbdFile){
    QXmlStreamReader xstr;
    QFile file;
    QString path = QString("%1%2").arg(kbdPath()).arg(kbdFile);
    // read keyboard xml
    file.setFileName(path);
    if (!file.exists()) {
        qDebug() << "KeyboardModel::loadKbd, failed for path=" << path;
        return;
    }
    file.open(QFile::ReadOnly | QFile::Text);
    xstr.setDevice(&file);
    // initialize the key count, accumulate in the readKey
    m_keyCount = 0;

    xstr.readNext();
    while (!xstr.atEnd()) {
        if (xstr.isStartElement()) {
            if (xstr.name() == "keyboard") {
                readKeyboard(&xstr);
            } else if (xstr.name() == "key"){
                readKey(&xstr);
            }
        }
        xstr.readNext();
    }
    if (xstr.hasError()) {
        qDebug() << "KeyboardModel::loadKbd errorString=" << xstr.errorString();
    }
    file.close();
    qDebug() << "KeyboardModel::loadKbd found keysCnt=" << m_keyCount;

    // reset the model
    beginResetModel();
    endResetModel();

    emit keyRowsChanged(keyRows());
    emit rowCellsChanged(rowCells());
    emit keySpacingChanged(keySpacing());
    emit currKbdChanged(currKbd());
}
//
void KeyboardModel::readKeyboard(QXmlStreamReader* pXmlReader)
{
    m_kbdName = pXmlReader->attributes().value("id").toString();
    m_keyRows = pXmlReader->attributes().value("row").toString().toInt();
    m_rowCells = pXmlReader->attributes().value("resolution").toString().toInt();
    m_keySpacing = pXmlReader->attributes().value("spacing").toString().toInt();

    qDebug() << "KeyboardModel::readKeyboard kbdName=" << m_kbdName
             << " keyRows=" << m_keyRows
             << " rowCells=" << m_rowCells
             << " spacing=" << m_keySpacing;
}
//
void KeyboardModel::readKey(QXmlStreamReader *pXmlReader){
    MyKey * pKey = nullptr;
    if(m_keyCount>=0 && m_keyCount< m_vecKeys.size()){
        pKey=m_vecKeys.at(m_keyCount);
    }else {
        pKey= new MyKey;
        m_vecKeys.append(pKey);
    }
    if(!pKey){
        qDebug() << "KeyboardModel::readKey Null Key!";
        return;
    }

    if(pXmlReader->attributes().hasAttribute("func")){
        pKey->isFunc=true;
        pKey->func=pXmlReader->attributes().value("func").toString();
    }else{
        pKey->isFunc=false;
        pKey->func = "";
    }

    if (pXmlReader->attributes().hasAttribute("icon")) {
        pKey->isIcon = true;
        pKey->pic = pXmlReader->attributes().value("icon").toString();
    } else {
        pKey->isIcon = false;
        pKey->pic = "";
    }

    pKey->span = pXmlReader->attributes().value("span").toString().toInt();

    if (pXmlReader->attributes().hasAttribute("seq")) {
        pKey->seq = pXmlReader->attributes().value("seq").toString();
    } else {
        pKey->seq = "";
    }

    if (pXmlReader->attributes().hasAttribute("color")) {
        pKey->keyColor = pXmlReader->attributes().value("color").toString();
    } else {
        pKey->keyColor = "";
    }

    pKey->text = pXmlReader->readElementText();
    if (pKey->text.isEmpty() && !pKey->isFunc && !pKey->isIcon) {
        pKey->isEmtpy = true;
    } else {
        pKey->isEmtpy = false;
    }

    pKey->printOut();

     m_keyCount++;
}

//
QString KeyboardModel::inputMode() const{
    return m_inputMode;
}
//
int KeyboardModel::keyRows() const
{
    return m_keyRows;
}

int KeyboardModel::rowCells() const
{
    return m_rowCells;
}

int KeyboardModel::keySpacing() const
{
    return m_keySpacing;
}

QString KeyboardModel::currKbd() const
{
    return m_kbdName;
}
//
QString KeyboardModel::currString() const{
    return m_currString;
}
void KeyboardModel::setCurrString(const QString &currStr)
{
    m_currString = currStr;
    emit currStringChanged(currString());
}

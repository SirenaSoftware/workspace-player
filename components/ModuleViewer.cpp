#include "ModuleViewer.h"
#include "helpers/common.h"
#include <QVBoxLayout>
#include <QDir>

ModuleViewer::ModuleViewer(QWidget *parent)
    : QWidget{parent}
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(0,0,0,0);
    layout()->setSpacing(0);

    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L,
                  "function registerWidget(userdata,id,setter,getter)"
                  "  _ENV[id] = setmetatable({userdata,setter,getter},{"
                  "    __index ="
                  "      function (self,k)"
                  "        local get_qobject_property = rawget(self,3)"
                  "        return get_qobject_property(rawget(self,1),k)"
                  "      end"
                  "    ;"
                  "    __newindex ="
                  "      function (self,k,v)"
                  "        local set_qobject_property = rawget(self,2)"
                  ""
                  "        if type(v) == 'function' then"
                  "          return rawset(self,k,v)"
                  "        end"
                  ""
                  "        set_qobject_property(rawget(self,1),k,v)"
                  "      end"
                  "    ;"
                  "  })"
                  "end");
}

void ModuleViewer::loadScript(QString fname){
    luaL_dofile(L,fname.toStdString().c_str());
}

void ModuleViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)

    QStyleOption option;
    option.initFrom(this);

    QPainter painter(this);

    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ModuleViewer::dumpComponentData(QWidget * parent, QFile *file) {
   QObjectList childrens = parent->children();
   QObjectList::iterator it = childrens.begin();

   while ( it != childrens.end() ) {
      QWidget* children = (QWidget *)(*it);

      QString widget_data = children->property("data").toString();
      bool descartable = children->property("descartable").toBool();
      bool separated = children->property("separated").toBool();
      bool edited = children->property("edited").toBool();

      if (edited&&!descartable&&separated&&children->objectName()!="") {

          QFile file(PATH+children->objectName()+".data");
          if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
              QTextStream out(&file);
              out << children->property("data").toString();
              file.close();
          }
      }

      if (!widget_data.isEmpty()&&children->objectName()!=""&&!descartable&&!separated) {
          file->write((children->objectName()+": \""+widget_data+"\"\n").toLocal8Bit());
      }

      dumpComponentData(children, file);
      ++it;
   }
}

void ModuleViewer::loadComponentData(QWidget * parent, QMap<QString,QString>*data){
    QObjectList childrens = parent->children();
    QObjectList::iterator it = childrens.begin();

    while ( it != childrens.end() ) {
       QWidget* children = (QWidget *)(*it);
       QString value = data->value(QString(children->objectName()));
       bool descartable = children->property("descartable").toBool();
       bool separated = children->property("separated").toBool();

       if (value != ""&&!descartable&&!separated) {
           children->setProperty("data",value);
       } else if (separated&&children->objectName()!="") {
           QFile file(PATH+children->objectName()+".data");
           if (file.open(QIODevice::ReadOnly)) {
               QTextStream in(&file);
               children->setProperty("data",in.readAll());
               file.close();
           }
       }

       loadComponentData(children, data);
       ++it;
    }
}

void ModuleViewer::writeData(QString fname){
    QFile file(fname);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.resize(0);

    dumpComponentData(this,&file);//&file);

    file.close();
}

void ModuleViewer::loadData(QString fname){
    QMap<QString,QString> data;

    PATH = fname.mid(0,fname.length()-4)+"/";
    QDir().mkdir(PATH);

    QFile file(fname);

    if (file.open(QFile::ReadOnly)){
        QTextStream file_data(&file);
        while (!file_data.atEnd()) {
            QStringList line = processSAMLLine(file_data.readLine());

            QString property = line[0];
            QString value = line[1];

            data[property] = value;
        }
        file.close();

        loadComponentData(this, &data);
        return;
    }

    print("File '"+fname+"' not found");
}

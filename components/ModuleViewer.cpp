#include "ModuleViewer.h"
#include <QVBoxLayout>

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

void ModuleViewer::dumpComponents(QWidget * parent, QFile *file) {
   QObjectList childrens = parent->children();
   while ( childrens.begin() != childrens.end() ) {
      QWidget * children = (QWidget *)(*childrens.begin()++);

      QString widget_data = children->property("data").toString();

      if (!widget_data.isEmpty()&&children->objectName()!="") {
          file->write((children->objectName()+": "+widget_data+"\n").toLocal8Bit());
      }

      dumpComponents(children, file);
   }
}

void ModuleViewer::writeData(QString fname){
    QFile file(fname);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.resize(0);

    dumpComponents(this,&file);

    file.close();
}

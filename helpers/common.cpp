#include "common.h"
#include <QDebug>
#include <QFile>

void print(QString message){
    qDebug() << message;
}

QStringList processSAMLLine(QString line){
    QString property = line.left(line.indexOf(":"));
    QString value = line.mid(line.indexOf(":")+1).trimmed();

    int i = 0;
    for(i = 0; i < property.size() && property[i] == ' '; ++i);

    if (value.left(1) == "\"" && value.right(1) == "\"") {
        value = value.mid(1,value.length()-2).toLocal8Bit();
    }

    return QStringList() << property.trimmed().remove(" ") << value << QString::number(i/2);
}

static int widget_set_property(lua_State* L) {
    QWidget *wdg = (QWidget *)lua_touserdata(L, 1);
    wdg->setProperty(lua_tostring(L,2),lua_tostring(L,3));

    lua_settop(L, 0);
    return 0;
}

static int widget_get_property(lua_State* L) {
    QWidget *wdg = (QWidget *)lua_touserdata(L, 1);
    QVariant value = wdg->property(lua_tostring(L,2));

    lua_settop(L, 0);
    lua_pushstring(L,value.toString().toStdString().c_str());
    return 1;
}

void registerWidgetOnLua(QWidget*widget,lua_State*L){
    lua_getglobal(L, "registerWidget"); // 2
    lua_pushlightuserdata(L,widget);
    lua_pushstring(L,widget->objectName().toStdString().c_str());
    lua_pushcfunction(L,widget_set_property);
    lua_pushcfunction(L,widget_get_property);
    lua_call(L,4,0);
}

QWidget*string2widget(QString id,QString type,ModuleViewer*page){
    QWidget*wdg = nullptr;

    if (type == "HBox") {
        wdg = new Box;
        wdg->setLayout(new QHBoxLayout);
        wdg->layout()->setContentsMargins(0,0,0,0);
        wdg->layout()->setSpacing(0);
        goto finalize;
    }

    if (type == "VBox") {
        wdg = new Box;
        wdg->setLayout(new QVBoxLayout);
        wdg->layout()->setContentsMargins(0,0,0,0);
        wdg->layout()->setSpacing(0);
        goto finalize;
    }

    if (type == "Button") {
        Button*btn = new Button;
        btn->L = page->L;
        wdg = btn;
        goto finalize;
    }

    wdg = new QWidget;

finalize:
    wdg->setObjectName(id);
    registerWidgetOnLua(wdg,page->L);
    return wdg;
}

void assingProperty(QWidget*widget,QString property, QString value) {
    if (property == "pos[x]") {
        widget->move(value.toInt(),widget->y());
        return;
    }

    if (property == "pos[y]") {
        widget->move(widget->x(),value.toInt());
        return;
    }

    if (property == "width") {
        widget->resize(value.toInt(),widget->height());
        return;
    }

    if (property == "height") {
        widget->resize(widget->width(),value.toInt());
        return;
    }

    if (property == "width[min]") {
        widget->setMinimumWidth(value.toInt());
        return;
    }

    if (property == "height[min]") {
        widget->setMinimumHeight(value.toInt());
        return;
    }

    if (property == "width[max]") {
        widget->setMaximumWidth(value.toInt());
        return;
    }

    if (property == "height[max]") {
        widget->setMaximumHeight(value.toInt());
        return;
    }

    if (property.startsWith("font[")) {
        QFont font = QFont(widget->font());

        if (property == "font[name]") {
            font.setFamily(value);
            widget->setFont(font);
            return;
        }

        if (property == "font[style]") {
            font.setStyleName(value);
            widget->setFont(font);
            return;
        }

        if (property == "font[size]") {
            font.setPointSize(value.toInt());
            widget->setFont(font);
            return;
        }

        if (property == "font[bold]") {
            font.setBold(value == "true");
            widget->setFont(font);
            return;
        }

        if (property == "font[italic]") {
            font.setItalic(value == "true");
            widget->setFont(font);
            return;
        }

        if (property == "font[underline]") {
            font.setItalic(value == "true");
            widget->setFont(font);
            return;
        }

        if (property == "font[overline]") {
            font.setOverline(value == "true");
            widget->setFont(font);
            return;
        }

        if (property == "font[strikeout]") {
            font.setStrikeOut(value == "true");
            widget->setFont(font);
            return;
        }

        if (property == "font[kerning]") {
            font.setKerning(value == "true");
            widget->setFont(font);
            return;
        }
    }

    if (widget->metaObject()->className()==QString("Box")&&widget->layout()) {
        int v = value.toInt();
        QMargins padding = QMargins(widget->layout()->contentsMargins());

        if (property == "padding") {
            widget->layout()->setContentsMargins(v,v,v,v);
            return;
        }

        if (property == "padding[top]") {
            padding.setTop(v);
            widget->layout()->setContentsMargins(padding);
            return;
        }

        if (property == "padding[left]") {
            padding.setLeft(v);
            widget->layout()->setContentsMargins(padding);
            return;
        }

        if (property == "padding[right]") {
            padding.setRight(v);
            widget->layout()->setContentsMargins(padding);
            return;
        }

        if (property == "padding[bottom]") {
            padding.setBottom(v);
            widget->layout()->setContentsMargins(padding);
            return;
        }

        if (property == "spacing") {
            widget->layout()->setSpacing(v);
            return;
        }

        if (property == "spacing[vertical]") {
            QGridLayout*gridLayout = dynamic_cast<QGridLayout*>(widget->layout());
            if (gridLayout) {
                gridLayout->setVerticalSpacing(v);
                return;
            }
            widget->layout()->setSpacing(v);
            return;
        }

        if (property == "spacing[horizontal]") {
            QGridLayout*gridLayout = dynamic_cast<QGridLayout*>(widget->layout());
            if (gridLayout) {
                gridLayout->setHorizontalSpacing(v);
                return;
            }
            widget->layout()->setSpacing(v);
            return;
        }
    }

    QString style_property = "widget_";

    if (property.startsWith("{item}")) {
        style_property = "item_";
        property.remove("{item}");
    }

    for (const QString &state : QList<QString> {"hover","pressed","focus","selected"} ) {
        if (property.startsWith(state)) {
            style_property += state;
            property.remove(state+"->");
            break;
        }
    }

    QString css = widget->property(style_property.toLocal8Bit()).toString();

    if (property == "color[background]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"background-color: "+value+";");
        return;
    }

    if (property == "color[foreground]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"color: "+value+";");
        return;
    }

    if (property == "color[alternate]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"alternate-background-color: "+value+";");
        return;
    }

    for (const QString &css_property : QList<QString> {"padding","margin","border"} ) {
        if (property == css_property){
            widget->setProperty(style_property.toLocal8Bit(),css+property+": "+value+";");
            return;
        }

        if (property.startsWith(css_property)) {
            for (const QString &place : QList<QString> {"top","left","right", "bottom"} ) {
                if (property == QString(css_property+"["+place+"]")) {
                    widget->setProperty(style_property.toLocal8Bit(),css+css_property+"-"+place+": "+value+";");
                    return;
                }
            }
            break;
        }
    }

    if (property == "radius") {
        widget->setProperty(style_property.toLocal8Bit(),css+"border-radius: "+value+";");
        return;
    }

    if (property == "radius[topLeft]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"border-top-left-radius: "+value+";");
        return;
    }

    if (property == "radius[topRight]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"border-top-right-radius: "+value+";");
        return;
    }

    if (property == "radius[bottomLeft]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"border-bottom-left-radius: "+value+";");
        return;
    }

    if (property == "radius[bottomRight]") {
        widget->setProperty(style_property.toLocal8Bit(),css+"border-bottom-right-radius: "+value+";");
        return;
    }

    widget->setProperty(("_"+property).toLocal8Bit(),value);
}

void buildStyleSheet(QWidget*widget){
    QString id = "#"+widget->objectName();
    QString stylesheet = "";

    for (const QString &level : QList<QString> {"widget_", "item_"} ) {
        for (const QString &state : QList<QString> {"", ":hover",":pressed",":focus",":selected"} ) {
            QString css_block = widget->property((level+state.mid(1)).toLocal8Bit()).toString();
            if (css_block != "") {
                stylesheet += id+(level=="item_"?"::item":"")+state+"{"+css_block+"}\n";
            }
        }
    }

    widget->setStyleSheet(stylesheet);
}

void loadLayout(QString layout_file,ModuleViewer*page){
    QFile file(layout_file);

    if (file.open(QFile::ReadOnly)){
        QTextStream file_data(&file);

        QMap<int,QWidget*>list;
        list[0] = page;

        QWidget*current_widget = nullptr;
        QWidget*parent_widget = page;

        QString id = "";

        while (!file_data.atEnd()) {
            QStringList line = processSAMLLine(file_data.readLine());

            QString property = line[0];
            QString value = line[1];
            int indent = line[2].toInt();

            parent_widget = list[indent];
            if (!parent_widget) continue;

            if (property == "id") {
                id = value;
                continue;
            }

            if (property == "type") {
                if (current_widget) {
                    buildStyleSheet(current_widget);
                }

                current_widget = string2widget(id,value,page);
                list[indent+1] = current_widget;

                if (parent_widget->layout()) {
                    parent_widget->layout()->addWidget(current_widget);
                    continue;
                }

                current_widget->setParent(parent_widget);
                continue;
            }

            if (property.startsWith("@")){
                assingProperty(page,property.mid(1),value);
                continue;
            }

            if (current_widget) {
                assingProperty(current_widget,property,value);
            }
        }

        if (current_widget) {
            buildStyleSheet(current_widget);
        }

        buildStyleSheet(page);

        file.close();
        return;
    }

    print("File '"+layout_file+"' not found");
}

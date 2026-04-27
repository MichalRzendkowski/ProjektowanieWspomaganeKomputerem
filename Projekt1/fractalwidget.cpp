#include "fractalwidget.h"

FractalWidget::FractalWidget(QWidget *parent) : QWidget{parent}{
    setupUI();
    addTransformations();

    elements.insert(new FractalElement(polyTemplate));
    markers.insert(new Marker(polyTemplate[0], 0, 1, 1));
    markers.insert(new Marker(polyTemplate[2], 0, scaleFactor, -1));

    updateElements();
}

void FractalWidget::setupUI(){
    mainLayout->addWidget(view, 1);
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);

    button1->setCheckable(true);
    button2->setCheckable(true);

    button1->setIcon(icon1);
    button1->setIconSize(iconSize);

    button2->setIcon(icon2);
    button2->setIconSize(iconSize);

    connect(button1, &QPushButton::toggled, this, [this](bool checked){
        if (checked){
            hideSuggestions();
            button2->setChecked(false);
            showSuggestions({1, 2, 3, 4, 5});
        }
        else
            hideSuggestions();
    });

    connect(button2, &QPushButton::toggled, this, [this](bool checked){
        if (checked){
            hideSuggestions();
            button1->setChecked(false);
            showSuggestions({-1});
        }
        else
            hideSuggestions();
    });

    setLayout(mainLayout);
    view->show();
}

void FractalWidget::addTransformations(){
    QTransform transform;
    transform.rotate(sideRotationAngle);
    auto polyRotated = transform.map(polyTemplate);

    for(int i = 1; i < 6; i++){
        Marker left = Marker(QPointF(0,0), 0.0, 1, i);
        Marker markerRightSide = Marker(polyRotated[0], sideRotationAngle, 1, (i + 1) % 6);
        Marker markerRightTop = Marker(polyRotated[2], sideRotationAngle, scaleFactor, -1);
        TransformationRight right = {polyRotated, markerRightSide, markerRightTop};
        grammar.insert(new Transformation(left, right));
    }

    transform.reset();
    transform.rotate(topRotationAngle);
    polyRotated = transform.map(polyTemplate);
    Marker left = Marker(polyRotated[0], 0.0, scaleFactor, -1);
    Marker markerRightSide = Marker(polyRotated[0], topRotationAngle, 1, 3);
    Marker markerRightTop = Marker(polyRotated[2], topRotationAngle, scaleFactor, -1);
    TransformationRight right = {polyRotated, markerRightSide, markerRightTop};
    grammar.insert(new Transformation(left, right));
}

void FractalWidget::updateElements(){
    foreach(auto e, elements)
        if (e->scene() == nullptr)
            scene->addItem(e);

    foreach(auto s, suggestions)
        if (s->scene() == nullptr)
            scene->addItem(s);

#ifdef SHOW_MARKERS
    foreach(auto m, markers){
        double r = 5.0 * m->size;
        scene->addEllipse(m->position.x() - r,
                          m->position.y() - r,
                          2 * r, 2 * r,
                          QPen(suggestionColor),
                          QBrush(Qt::NoBrush));
    }
#endif //SHOW_MARKERS

    scene->update();
}

void FractalWidget::applyTransformation(Transformation* t, Marker* m){
    QPolygonF polyTranslated = translatePoly(t->rightSide.poly, m);
    elements.insert(new FractalElement(polyTranslated));

    Marker* sideMarker = new Marker(t->rightSide.markerSide);
    sideMarker->rotation += m->rotation;
    sideMarker->size  = m->size;
    sideMarker->position = polyTranslated[0];

    Marker* topMarker = new Marker(t->rightSide.markerTop);
    topMarker->rotation += m->rotation;
    topMarker->size *= m->size;
    topMarker->position = polyTranslated[2];

    if(notNull(sideMarker)) markers.insert(sideMarker);
    if(notNull(topMarker)) markers.insert(topMarker);

    markers.remove(m);
    delete m;
}

void FractalWidget::showSuggestions(QVector<int> types){
    foreach(auto m, markers){
        if (!types.contains(m->type))
            continue;

        foreach(auto t, grammar){
            if (!matchTransformation(t, m))
                continue;

            QPolygonF polyTransformed = translatePoly(t->rightSide.poly, m);
            auto f = new FractalElement(polyTransformed);
            f->setColor(suggestionColor);
            f->setMarker(m);

            connect(f, &FractalElement::clicked,
                    this, &FractalWidget::onSuggestionClicked);

            suggestions.insert(f);
        }
    }

    updateElements();
}

QPolygonF FractalWidget::translatePoly(QPolygonF poly, Marker *m){
    QTransform t;
    t.rotate(m->rotation);
    t.scale(m->size, m->size);
    QPolygonF polyRotated = t.map(poly);
    t.reset();
    t.translate(m->position.x(), m->position.y());
    return t.map(polyRotated);
}


void FractalWidget::hideSuggestions(){
    foreach(auto s, suggestions)
        if (s->scene() != nullptr){
            scene->removeItem(s);
            s->setParent(nullptr);
            s->deleteLater();
        }

    suggestions.clear();
}

void FractalWidget::onSuggestionClicked(Marker* m){
    foreach(auto t, grammar)
        if(matchTransformation(t, m))
            applyTransformation(t, m);

    hideSuggestions();
    if(button1->isChecked())
        showSuggestions({1, 2, 3, 4, 5});
    if(button2->isChecked())
        showSuggestions({-1});
    updateElements();
}

bool FractalWidget::matchTransformation(Transformation* t, Marker* m){
    return notNull(m) && t->leftSide.type == m->type;
}

bool FractalWidget::notNull(Marker* m){
    return m->type != 0;
}

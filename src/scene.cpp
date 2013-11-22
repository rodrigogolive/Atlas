#include <QList>
#include <QRectF>
#include <QPainter>

#include "scene.h"

Scene::Scene()
    : QGraphicsScene()
    , m_currentSize(QSize(800, 800)) // XXX we need to change it as the user adds new images
    , m_drawInfoLayer(false)
{
    setBackgroundBrush(QPixmap("../images/transparency.png"));

    QPixmap *firstLayer = new QPixmap(m_currentSize);
    firstLayer->fill(Qt::transparent);
    m_imageLayer = addPixmap(*firstLayer);

    QPixmap *secondLayer = new QPixmap(m_currentSize);
    secondLayer->fill(Qt::transparent);
    m_informationLayer = addPixmap(*secondLayer);
}

Scene::~Scene()
{
}

void Scene::addImages(const QStringList files)
{
    // XXX recalculate the bounding box size INCLUDING the size of the new added images,
    // finding the smallest bounding box for them (2d packing problem), and adjusting
    // m_currentSize as well
    QPixmap *layer = new QPixmap(m_currentSize);
    layer->fill(Qt::transparent);

    QPainter p(layer);
    foreach (QString fileName, files) {
        QPixmap *pixmap = new QPixmap(fileName);
        p.drawPixmap(0, 0, *pixmap); // XXX will use calculated positions to address correct pos

        m_pixmapList.push_back(pixmap); // XXX really it will be on another structure soon
    }
    p.end();

    // update main pixmap
    m_imageLayer->setPixmap(*layer);

    if (m_drawInfoLayer)
        drawInfoLayer();
}

void Scene::saveImage(const QString fileName)
{
    m_imageLayer->pixmap().save(fileName);
}

void Scene::drawInformationsLayer(bool draw)
{
    if (m_drawInfoLayer == draw)
        return;

    m_drawInfoLayer = draw;
}

void Scene::drawInfoLayer()
{
    QPixmap *layer = new QPixmap(m_currentSize);
    layer->fill(Qt::transparent);

    QPainter p(layer);
    QPen pen;

    pen.setColor(Qt::red);
    pen.setWidth(3);
    p.setPen(pen);

    foreach (QPixmap *pixmap, m_pixmapList) {
        p.drawRect(pixmap->rect());
    }

    p.end();

    m_informationLayer->setPixmap(*layer);
}

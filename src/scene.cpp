#include <QList>
#include <QRectF>
#include <QPainter>

#include "scene.h"
#include <QDebug>

// ImageItem
ImageItem::ImageItem(QPixmap *image)
{
    m_image = image;
    m_pos = QPoint(0, 0);
}
ImageItem::~ImageItem()
{
    if (m_image)
        delete m_image;
}

QPixmap *ImageItem::pixmap()
{
    return m_image;
}

QSize ImageItem::size() const
{
    if (!m_image)
        return QSize(0, 0);

    return m_image->size();

}

QPoint ImageItem::pos() const
{
    return m_pos;
}

void ImageItem::setPos(const QPoint pos)
{
    m_pos = pos;
}

QRect ImageItem::rect() const
{
    return QRect(m_pos, size());
}


// Scene
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
    foreach (ImageItem *image, m_imageList) {
        delete image;
    }
}

void Scene::addImages(const QStringList files)
{
    // XXX recalculate the bounding box size INCLUDING the size of the new added images,
    // finding the smallest bounding box for them (2d packing problem), and adjusting
    // m_currentSize as well
    QPixmap *layer = new QPixmap(m_currentSize);
    layer->fill(Qt::transparent);

    // XXX split draw and insertion
    QPainter p(layer);
    foreach (QString fileName, files) {
        QPixmap *pixmap = new QPixmap(fileName);
        QPoint newPos = QPoint(0, 0);

        if (m_imageList.size() != 0) {
            newPos = m_imageList[m_imageList.size() - 1]->pos() +
                QPoint(pixmap->size().width(), 0);
        }

        p.drawPixmap(newPos, *pixmap); // XXX will use calculated positions to address correct pos
        qDebug() << newPos;

        ImageItem *image = new ImageItem(pixmap);
        qDebug() << image->rect();
        image->setPos(newPos);
        m_imageList.push_back(image);
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

    foreach (ImageItem *image, m_imageList) {
        p.drawRect(image->rect());
    }

    p.end();

    m_informationLayer->setPixmap(*layer);
}

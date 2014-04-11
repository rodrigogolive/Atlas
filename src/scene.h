#ifndef __SCENE_H__
#define __SCENE_H__

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QList>

class ImageItem
{
public:
    ImageItem(QPixmap *image);
    ~ImageItem();

    QPixmap *pixmap();

    QSize size() const;
    QPoint pos() const;
    QRect rect() const;

private:
    QPixmap *m_image;
    QPoint m_pos;
};


typedef QList<ImageItem *> ImageItemList;
typedef QList<QPixmap *> QPixmapList;

class Scene: public QGraphicsScene
{
public:
    Scene();
    ~Scene();

    void drawInformationsLayer(bool draw = true);

    void addImages(const QStringList files);
    void saveImage(const QString fileName);

private:
    void drawInfoLayer();

    QGraphicsPixmapItem *m_imageLayer; // display all images
    QGraphicsPixmapItem *m_informationLayer; // draw image info on top of the above layer

    ImageItemList m_imageList; // all images added to the scene

    QSize m_currentSize;

    bool m_drawInfoLayer;
};

#endif // __SCENE_H__

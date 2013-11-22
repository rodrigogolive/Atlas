#ifndef __SCENE_H__
#define __SCENE_H__

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QList>

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

    // XXX we'll need to access each pixmap's rect for the
    // packing calculation; should we create a custom class to handle
    // the image list, rectangles, positions, algorithms, ...?
    QPixmapList m_pixmapList; // all images added to the scene

    QSize m_currentSize;

    bool m_drawInfoLayer;
};

#endif // __SCENE_H__

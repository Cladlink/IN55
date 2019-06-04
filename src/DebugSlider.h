#ifndef DEBUGSLIDER_H
#define DEBUGSLIDER_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

class QSlider;
class QLabel;

class DebugSlider : public QWidget
{
    Q_OBJECT

    QSlider* slider;
    QLabel* label;
    float sliderGranularity;
    float min;
    float max;

private slots:
    void sliderValueChanged();

signals:
        void valueChanged(float newValue);

public:
    DebugSlider(float value = 0.0f,
        float min = -10.0f, float max = 10.0f,
        bool textOnLeft = false, float granularity = 40.0);
    float value() const;
    void setValue(float newValue);
};

#endif // DEBUGSLIDER_H

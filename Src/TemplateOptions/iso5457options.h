#ifndef ISO5457OPTIONS_H
#define ISO5457OPTIONS_H

#include <QObject>

class ISO5457Options : public QObject
{
    Q_OBJECT
private:
    ///
    /// \brief trimmingMarks a boolean to save if trimming marks should be showm or not
    ///
    bool trimmingMarks;
public:
    explicit ISO5457Options(QObject *parent = nullptr);

    bool getTrimmingMarks() const;
    void setTrimmingMarks(bool newTrimmingMarks);

signals:

};

#endif // ISO5457OPTIONS_H

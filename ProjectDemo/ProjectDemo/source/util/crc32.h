#ifndef __CRC32_H
#define __CRC32_H

#include <QMutex>
class CRC32
{
public:
    static CRC32 *globalInstance();
    ~CRC32();

    quint32 cyg_crc32(quint8 *s, quint32 len);
    quint32 cyg_ether_crc32(quint8 *s, quint32 len);
private:

    static QMutex   m_mutex;
    static CRC32* m_pInstance;

    CRC32();

    quint32 cyg_crc32_accumulate(quint32 crc32val, quint8 *s, quint32 len);
    quint32 cyg_ether_crc32_accumulate(quint32 crc32val, quint8 *s, quint32 len);
};


#endif


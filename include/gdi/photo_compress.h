#pragma once
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

namespace y
{
/**
 * @brief ͼƬ����ѹ���㷨,�ɴ����غ�����2��ά�Ƚ�������ѹ��
 * 
 *  CompressPixel   : ѹ��ͼƬ����
 *  CompressQuality : ѹ��ͼƬ����
 */
class CPhotoCompress
{
public:
    /**
     * @brief ѹ��ͼƬ����
     * @param lpOriFilePath Դ�ļ�·��
     * @param lpDestFilePah ѹ�����Ŀ���ļ�·��
     * @param uNewWidth     �µĿ������ֵ
     * @param uNewHeigth    �µĸ߶�����ֵ
     */
    static bool CompressPixel(LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, UINT uNewWidth, UINT uNewHeigth);

    /**
     * @brief ѹ��ͼƬ����
     * @param lpOriFilePath Դ�ļ�·��
     * @param lpDestFilePah ѹ�����Ŀ���ļ�·��
     * @param quality       ѹ����
     */
    static bool CompressQuality(LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, ULONG quality = 30 );

private:
    static bool _CompressPixel( LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, UINT uNewWidth, UINT uNewHeigth );
    static bool _CompressPixelImpl(Gdiplus::Image* pImage, UINT uNewWidth, UINT uNewHeigth, LPCTSTR lpDestFilePah);
    static bool _CompressQuality( LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, ULONG quality );
    static bool _CompressQualityImpl(Gdiplus::Image* pImage, LPCTSTR lpDestFilePah, ULONG quality);
    static bool _GetEncoderClsid(LPCTSTR lpFormat, CLSID* pClsid);
};

namespace photo_compress_utils
{
    // auto initialize and un-initialize gdi+ environment
    class CGdiEnvGuard
    {
    public:
        CGdiEnvGuard() : m_gdiplusToken(0) , m_bIsGdiplusOk(false)
        {
            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
            if (Gdiplus::Ok == Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL))
            {
                m_bIsGdiplusOk = true;
            }
            else
            {
                m_bIsGdiplusOk = false;
            }
        }

        ~CGdiEnvGuard()
        {
            if (m_bIsGdiplusOk)
            {
                Gdiplus::GdiplusShutdown(m_gdiplusToken);
            }
        }

        bool IsGdiplusOk() const { return m_bIsGdiplusOk; }

    private:
        ULONG_PTR m_gdiplusToken;
        bool      m_bIsGdiplusOk;
    };
} // end of namespace photo_compression_utils

inline bool CPhotoCompress::CompressPixel( LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, UINT uNewWidth, UINT uNewHeigth )
{
    bool bRet = false;

    if (lpOriFilePath && lpDestFilePah)
    {
        photo_compress_utils::CGdiEnvGuard guard;
        if (guard.IsGdiplusOk())
        {
            bRet = _CompressPixel(lpOriFilePath, lpDestFilePah, uNewWidth, uNewHeigth);
        }
    }

    return bRet;
}

inline bool CPhotoCompress::CompressQuality( LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, ULONG quality )
{
    bool bRet = false;

    if (lpOriFilePath && lpDestFilePah)
    {
        photo_compress_utils::CGdiEnvGuard guard;
        if (guard.IsGdiplusOk())
        {
            bRet = _CompressQuality(lpOriFilePath, lpDestFilePah, quality);
        }
    }

    return bRet;
}

inline bool CPhotoCompress::_CompressPixel( LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, UINT uNewWidth, UINT uNewHeigth )
{
    bool bRet = false;
    Gdiplus::Image* pImage = new Gdiplus::Image(lpOriFilePath);
    bRet = _CompressPixelImpl(pImage, uNewWidth, uNewHeigth, lpDestFilePah);
    delete pImage;

    return bRet;
}

inline bool CPhotoCompress::_CompressPixelImpl( Gdiplus::Image* pImage, UINT uNewWidth, UINT uNewHeigth, LPCTSTR lpDestFilePah )
{
    bool                bRet        = false;
    Gdiplus::Bitmap*    pTempBitmap = NULL;
    Gdiplus::Graphics*  pGraphics   = NULL;
    UINT                unOriHeight = pImage->GetHeight();
    UINT                unOriWidth  = pImage->GetWidth();

    do
    {
        if (unOriWidth < 1 || unOriHeight < 1)
        {
            break;
        }

        CLSID encoderClsid;
        if (!_GetEncoderClsid(L"image/jpeg", &encoderClsid))
        {
            break;
        }

        pTempBitmap = new Gdiplus::Bitmap(uNewWidth, uNewHeigth);
        pGraphics   = Gdiplus::Graphics::FromImage(pTempBitmap);
        if (!pGraphics)
        {
            break;
        }

        if (Gdiplus::Ok != pGraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQuality))
        {
            break;
        }

        if (Gdiplus::Ok != pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality))
        {
            break;
        }

        Gdiplus::RectF RectDest( 0.0f, 0.0f, (Gdiplus::REAL)uNewWidth, (Gdiplus::REAL)uNewHeigth);
        if (Gdiplus::Ok != pGraphics->DrawImage(pImage, RectDest, 0.0f, 0.0f, (Gdiplus::REAL)unOriWidth,
            (Gdiplus::REAL)unOriHeight, Gdiplus::UnitPixel, NULL, NULL, NULL))
        {
            break;
        }

        if (Gdiplus::Ok != pTempBitmap->Save(lpDestFilePah, &encoderClsid, NULL))
        {
            break;
        }

        bRet = true;
    } while(0);

    if (pGraphics)   delete pGraphics;
    if (pTempBitmap) delete pTempBitmap;

    return bRet;
}

inline bool CPhotoCompress::_CompressQuality( LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah, ULONG quality )
{
    bool bRet = false;
    Gdiplus::Image* pImage = new Gdiplus::Image(lpOriFilePath);
    bRet = _CompressQualityImpl(pImage, lpDestFilePah, quality);
    delete pImage;

    return bRet;
}

inline bool CPhotoCompress::_CompressQualityImpl( Gdiplus::Image* pImage, LPCTSTR lpDestFilePah, ULONG quality )
{
    bool bRet = false;

    do
    {
        UINT uHeight = pImage->GetHeight();
        UINT uWidth  = pImage->GetWidth();
        if (uWidth < 1 || uHeight < 1)
        {
            break;
        }

        CLSID encoderClsid;
        if (!_GetEncoderClsid(L"image/jpeg", &encoderClsid))
        {
            break;
        }

        Gdiplus::EncoderParameters param;
        param.Count                         = 1;
        param.Parameter[0].Guid             = Gdiplus::EncoderQuality;
        param.Parameter[0].Type             = Gdiplus::EncoderParameterValueTypeLong;
        param.Parameter[0].NumberOfValues   = 1;
        param.Parameter[0].Value            = &quality;

        if (Gdiplus::Ok != pImage->Save(lpDestFilePah, &encoderClsid, &param))
        {
            break;
        }

        bRet = true;
    } while(0);

    return bRet;
}

inline bool CPhotoCompress::_GetEncoderClsid( LPCTSTR lpFormat, CLSID* pClsid )
{
    bool bRet             = false;
    UINT uNumEncoders     = 0;
    UINT uNumEncodersSize = 0;
    Gdiplus::GetImageEncodersSize(&uNumEncoders, &uNumEncodersSize);
    if (0 == uNumEncodersSize)
    {
        return false;
    }

    Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(uNumEncodersSize));

    Gdiplus::GetImageEncoders(uNumEncoders, uNumEncodersSize, pImageCodecInfo);

    for (UINT i = 0; i < uNumEncoders; ++i)
    {
        if (wcscmp(pImageCodecInfo[i].MimeType, lpFormat) == 0)
        {
            *pClsid = pImageCodecInfo[i].Clsid;
            bRet = true;
            break;
        }    
    }

    free(pImageCodecInfo);
    return bRet;
}

} // end of namespace y
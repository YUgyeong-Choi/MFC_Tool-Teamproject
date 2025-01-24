#include "pch.h"
#include "CFileInfo.h"

CString CFileInfo::Convert_RelativePath(CString strFullPath)
{
    TCHAR   szRelativePath[MAX_PATH] = L"";
    TCHAR   szCurDirPath[MAX_PATH] = L"";

    GetCurrentDirectory(MAX_PATH, szCurDirPath);

    // PathRelativePathTo : 절대 경로를 상대 경로로 변환

    // szCurDirPath에서 strFullPath로 가는 상대 경로를 구해서 szRelativePath 저장
    // 주의 사항 : 같은 드라이브 안에서만 경로 변경이 가능

    PathRelativePathTo(szRelativePath,
                        szCurDirPath,
                        FILE_ATTRIBUTE_DIRECTORY,
                        strFullPath.GetString(),
                        FILE_ATTRIBUTE_DIRECTORY);

    return CString(szRelativePath);
}

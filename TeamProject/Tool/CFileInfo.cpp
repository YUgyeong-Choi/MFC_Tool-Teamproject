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

void CFileInfo::DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList)
{
    // CFileFind : mfc 에서 제공하는 파일 및 경로 제어 관련 클래스
    CFileFind       Find;

    wstring     wstrFilePath = wstrPath + L"\\*.*";
    // FindFile : 매개 변수로 전달된 경로에 파일의 유무를 확인하는 함수

    BOOL    bContinue = Find.FindFile(wstrFilePath.c_str());

    while (bContinue)
    {
        // FindNextFile : 동일 경로 안에서 다음 파일을 찾는 함수, 찾을 게 없을 경우 또는 마지막 대상을 찾았을 경우 0을 반환

        bContinue = Find.FindNextFile();

        if (Find.IsDots())
            continue;

        else if (Find.IsDirectory())
        {
            DirInfoExtraction(wstring(Find.GetFilePath()), rPathInfoList);
        }
        else
        {
            if (Find.IsSystem())
                continue;

            IMGPATH* pImgPath = new IMGPATH;
            TCHAR   szPathBuf[MAX_PATH] = L"";

            lstrcpy(szPathBuf, Find.GetFilePath().GetString());

            PathRemoveFileSpec(szPathBuf);

            pImgPath->iCount = DirFileCount(szPathBuf);

            // 1. 파일의 이름만 얻어오자

            // GetFileTitle : 파일 이름만 얻어오는 함수
            wstring     wstrTextureName = Find.GetFileTitle().GetString();

            // 2. 파일의 이름 중 마지막 글자만 잘라내자
            // substr(시작, 끝) : 시작에서 끝에 해당하는 문자만 잘라냄
            wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

            // 3. 마지막 글자 위치에 %d를 결합하자      
            //     PathCombine(결과 값, src1, src2)
            // src1과 src2를 이어 붙여 완성된 경로를 결과 값의 위치에 저장
            // src1과 src2 사이에 \\ 자동으로 삽입
            PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());

            pImgPath->wstrPath = Convert_RelativePath(szPathBuf);
            //D:\유준환\151기\Frame151\Texture\Stage\Effect\BossMultiAttack\BossMultiAttack%d.png

            PathRemoveFileSpec(szPathBuf);
            //..\Frame151\Texture\Stage\Effect\BossMultiAttack

            // PathFindFileName : 파일명을 찾거나 가장 말단의 폴더명을 찾아냄
            pImgPath->wstrStateKey = PathFindFileName(szPathBuf);

            PathRemoveFileSpec(szPathBuf);
            //..\Frame151\Texture\Stage\Effect\

            // PathFindFileName : 파일명을 찾거나 가장 말단의 폴더명을 찾아냄
            pImgPath->wstrObjKey = PathFindFileName(szPathBuf);

            rPathInfoList.push_back(pImgPath);

            bContinue = 0;
        }
    }
}

int CFileInfo::DirFileCount(const wstring& wstrPath)
{

    // CFileFind : mfc 에서 제공하는 파일 및 경로 제어 관련 클래스
    CFileFind       Find;

    wstring     wstrFilePath = wstrPath + L"\\*.*";

    // FindFile : 매개 변수로 전달된 경로에 파일의 유무를 확인하는 함수

    BOOL    bContinue = Find.FindFile(wstrFilePath.c_str());

    int     iFileCnt(0);

    while (bContinue)
    {
        // FindNextFile : 동일 경로 안에서 다음 파일을 찾는 함수, 찾을 게 없을 경우 또는 마지막 대상을 찾았을 경우 0을 반환

        bContinue = Find.FindNextFile();

        if (Find.IsDots())
            continue;

        if (Find.IsSystem())
            continue;

        iFileCnt++;
    }

    return iFileCnt;
}

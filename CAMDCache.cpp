#include "CAMDCache.h"

#include "CoreWin.h"

CAMDCache::CAMDCache()
{
	::LoadLibraryA("D3D12.dll");
	::LoadLibraryA("D3D12Core.dll");
	::LoadLibraryA("D3DSCache.dll");
	::LoadLibraryA("userenv.dll");
	::LoadLibraryA("twinapi.appcore.dll");
	::LoadLibraryA("dxilconv.dll");
}

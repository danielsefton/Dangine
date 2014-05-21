#ifndef STABLEHEADERS_H
#define STABLEHEADERS_H

#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <deque>

#if !defined(NOMINMAX) && defined(_MSC_VER)
#	define NOMINMAX // required to stop windows.h messing up std::min
#endif

#include <WinSock2.h>
#include <Windows.h>

#include <d3dx9.h>
#include <OIS/OIS.h>

/*#include <RakNet/RakPeerInterface.h>
#include <RakNet/NetworkIDManager.h>
#include <RakNet/ReplicaManager3.h>
#include <RakNet/BitStream.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/Kbhit.h>
#include <RakNet/RakSleep.h>
#include <RakNet/GetTime.h>*/

#include "Util/Math/vmInclude.h"
#include "Util/Math/AxisAlignedBox.h"
#include "Util/Helper/Common.h"
#include "Util/Helper/Assert.h"
#include "Util/Helper/StringUtil.h"
#include "Util/Helper/Log.h"
#include "Util/Helper/Timer.h"
#include "Util/Memory/Memory.h"
#include "Util/Entity/EntityManager.h"

#endif // STABLEHEADERS_H
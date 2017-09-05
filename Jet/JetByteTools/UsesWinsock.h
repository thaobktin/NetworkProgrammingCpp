#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_WIN32_USES_WINSOCK_INCLUDED__
#define JETBYTE_TOOLS_WIN32_USES_WINSOCK_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: UsesWinsock.h $
// Version        : $Revision: 5 $
// Function       : 
//
// Author         : $Author: Len $
// Date           : $Date: 9/08/02 11:17 $
//
// Notes          : 
//
// Modifications  :
//
// $Log: /Web Articles/SocketServers/OpenSSLEchoServer/JetByteTools/Win32Tools/UsesWinsock.h $
// 
// 5     9/08/02 11:17 Len
// Removed the include for windows.h as it fails to compile with the
// latest platform sdk !
// 
// 4     9/08/02 11:10 Len
// Include windows.h before winsock2.h so that the code can compile with
// earlier versions of the platform SDK.
// 
// 3     20/05/02 23:17 Len
// Updated copyright and disclaimers.
// 
// 2     10/05/02 19:25 Len
// Lint options and code cleaning.
// 
// 1     9/05/02 18:47 Len
// 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1997 - 2002 JetByte Limited.
//
// JetByte Limited grants you ("Licensee") a non-exclusive, royalty free, 
// licence to use, modify and redistribute this software in source and binary 
// code form, provided that i) this copyright notice and licence appear on all 
// copies of the software; and ii) Licensee does not utilize the software in a 
// manner which is disparaging to JetByte Limited.
//
// This software is provided "as is" without a warranty of any kind. All 
// express or implied conditions, representations and warranties, including
// any implied warranty of merchantability, fitness for a particular purpose
// or non-infringement, are hereby excluded. JetByte Limited and its licensors 
// shall not be liable for any damages suffered by licensee as a result of 
// using, modifying or distributing the software or its derivatives. In no
// event will JetByte Limited be liable for any lost revenue, profit or data,
// or for direct, indirect, special, consequential, incidental or punitive
// damages, however caused and regardless of the theory of liability, arising 
// out of the use of or inability to use software, even if JetByte Limited 
// has been advised of the possibility of such damages.
//
// This software is not designed or intended for use in on-line control of 
// aircraft, air traffic, aircraft navigation or aircraft communications; or in 
// the design, construction, operation or maintenance of any nuclear 
// facility. Licensee represents and warrants that it will not use or 
// redistribute the Software for such purposes. 
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//lint -esym(1704, CUsesWinsock::CUsesWinsock)   private (copy) constructor
//lint -e537 repeated include (winsock2.h)
//
///////////////////////////////////////////////////////////////////////////////

#include <winsock2.h>

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CUsesWinsock
///////////////////////////////////////////////////////////////////////////////

class CUsesWinsock
{
   public :
   
      CUsesWinsock();
      
      ~CUsesWinsock();

   private :

      WSADATA m_data;

      // No copies do not implement
      CUsesWinsock(const CUsesWinsock &rhs);
      CUsesWinsock &operator=(const CUsesWinsock &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

#endif //JETBYTE_TOOLS_WIN32_USES_WINSOCK_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////


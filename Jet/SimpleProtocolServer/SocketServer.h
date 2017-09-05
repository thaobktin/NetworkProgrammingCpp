#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef SIMPLE_PROTOCOL_SERVER_SOCKET_SERVER_INCLUDED__
#define SIMPLE_PROTOCOL_SERVER_SOCKET_SERVER_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile: SocketServer.h $
// Version        : $Revision: 3 $
// Function       : 
//
// Author         : $Author: Len $
// Date           : $Date: 12/08/02 12:56 $
//
// Notes          : 
//
// Modifications  :
//
// $Log: /Web Articles/SocketServers/SimpleProtocolServer/SimpleProtocolServer/SocketServer.h $
// 
// 3     12/08/02 12:56 Len
// Handle new connection reset and connection error events.
// 
// 2     15/07/02 13:44 Len
// Buffers and sockets are now flushed when we shutdown the server rather
// than in the server's destructor. This removes the need for us to flush
// them to ensure we get the notifications. 
// 
// 1     30/06/02 13:52 Len
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
//
// Private constructor
//lint -esym(1704, CSocketServer::CSocketServer)
//
// No default constructor
//lint -esym(1712, CSocketServer)
//
///////////////////////////////////////////////////////////////////////////////

#include "JetByteTools\Win32Tools\SocketServer.h"
#include "JetByteTools\Win32Tools\tstring.h"

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools
{
   namespace Win32
   {
      class CIOCompletionPort;
   }
}

class CSocketServer : public JetByteTools::Win32::CSocketServer
{
   public :

      CSocketServer(
         const std::string &welcomeMessage,
         unsigned long addressToListenOn,
         unsigned short portToListenOn,
         size_t maxFreeSockets,
         size_t maxFreeBuffers,
         size_t bufferSize = 1024,
         size_t numThreads = 0);

   private :

      virtual void OnStartAcceptingConnections();
      virtual void OnStopAcceptingConnections();
      virtual void OnShutdownInitiated();
      virtual void OnShutdownComplete();

      virtual void OnConnectionCreated();
      virtual void OnConnectionEstablished(
         Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pAddress);
      virtual void OnConnectionClientClose(
         Socket *pSocket);
      virtual void OnConnectionReset(
          Socket *pSocket);
      virtual bool OnConnectionClosing(
         Socket *pSocket);
      virtual void OnConnectionClosed(
         Socket *pSocket);
      virtual void OnConnectionDestroyed();

      virtual void OnConnectionError(
         ConnectionErrorSource source,
         Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pBuffer,
         DWORD lastError);

      virtual void OnError(
         const JetByteTools::Win32::_tstring &message);

      virtual void OnBufferCreated();
      virtual void OnBufferAllocated();
      virtual void OnBufferReleased();
      virtual void OnBufferDestroyed();

      virtual void OnThreadCreated();
      virtual void OnThreadBeginProcessing();
      virtual void OnThreadEndProcessing();
      virtual void OnThreadDestroyed();

      virtual void ReadCompleted(
         Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pBuffer);

      size_t GetMinimumMessageSize() const;

      size_t GetMessageSize(
         const JetByteTools::Win32::CIOBuffer *pBuffer) const;

      JetByteTools::Win32::CIOBuffer *ProcessDataStream(
         Socket *pSocket,
         JetByteTools::Win32::CIOBuffer *pBuffer) const;

      void ProcessCommand(
         Socket *pSocket,
         const JetByteTools::Win32::CIOBuffer *pBuffer) const;

      const std::string m_welcomeMessage;

      // No copies do not implement
      CSocketServer(const CSocketServer &rhs);            
      CSocketServer &operator=(const CSocketServer &rhs); 
};

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

#endif // SIMPLE_PROTOCOL_SERVER_SOCKET_SERVER_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////

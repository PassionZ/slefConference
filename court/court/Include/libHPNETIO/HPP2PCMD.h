//HPP2PCMD.h
#ifndef __HPP2PCMD_H__
#define __HPP2PCMD_H__

enum {
	HPP2P_STT=0,			//P2PID+(USHORT)STTID+CID
	HPP2P_STT_ACK,			//P2PID+(USHORT)STTID+CID
	HPP2P_RTT,				//P2PID+(USHORT)RTTID
	HPP2P_RTT_ACK,			//P2PID+(USHORT)RTTID
	HPP2P_MTU,				//P2PID+(UCHAR)MTUID+(USHORT)MTU+DATA
	HPP2P_MTU_ACK,			//P2PID+(UCHAR)MTUID+(USHORT)MTU
	HPP2P_DATA,				//P2PID+(USHORT)LEN+DATA
	HPP2P_STUN=254,			//P2PID
	HPP2P_STUN_ACK=255,		//P2PID+NATIP+NATPORT
};


const int HPRTP_VERSION = 2;

/// RTP packet header
struct HPRTPHeaderStruct
{
#if (1)
    unsigned short count:4;              // csrc count
    unsigned short extension:1;          // header extension flag
    unsigned short padding:1;            // padding flag - for encryption
    unsigned short version:2;            // protocol version


    unsigned short type:7;               // payload type
    unsigned short marker:1;             // marker bit - for profile
#else

    unsigned char version:2;             // protocol version
    unsigned char padding:1;             // padding flag - for encryption
    unsigned char extension:1;           // header extension flag
    unsigned char count:4;               // csrc count

    unsigned char marker:1;              // marker bit - for profile
    unsigned char type:7;                // payload type


#endif

    unsigned short sequence;          // sequence number of this packet 
                                    // (needs endian conversion here, 
                                    // done in the access methods )

    /// timestamp of this packet
    unsigned long timestamp;
    /// source of packet
    unsigned long ssrc;
};

typedef struct HPRTPHeaderStruct HPRTPHeader;



#endif
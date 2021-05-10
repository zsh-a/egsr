/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef GRP_HEADER_H
#define GRP_HEADER_H

#include <stdint.h>
#include <vector>
#include "ns3/header.h"
#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"

namespace ns3 {

struct JunInfo
{
    uint8_t jid;
    int version;
    std::vector<int> list;

    JunInfo()
    {

    }

};

namespace grp {

double EmfToSeconds (uint8_t emf);
uint8_t SecondsToEmf (double seconds);

uint64_t LocToUint64 (int64_t loc);
int64_t Uint64ToLoc (uint64_t uin);

class BlockPacketHeader : public Header
{
public:
	BlockPacketHeader();
	virtual ~BlockPacketHeader();

	static TypeId GetTypeId (void);
	virtual TypeId GetInstanceTypeId (void) const;
	virtual void Print (std::ostream &os) const;
	virtual uint32_t GetSerializedSize (void) const;
	virtual void Serialize (Buffer::Iterator start) const;
	virtual uint32_t Deserialize (Buffer::Iterator start);


private:
	Ipv4Address m_addr;
  	uint32_t m_speed;
  	uint64_t m_posx;
  	uint64_t m_posy;

};



class CtrPacketHeader : public Header
{
public:
  CtrPacketHeader ();
  virtual ~CtrPacketHeader ();

  /**
   * Set the packet total length.
   * \param length The packet length.
   */
  void SetPacketLength (uint16_t length)
  {
    m_packetLength = length;
  }

  /**
   * Get the packet total length.
   * \return The packet length.
   */
  uint16_t GetPacketLength () const
  {
    return m_packetLength;
  }

  /**
   * Set the packet sequence number.
   * \param seqnum The packet sequence number.
   */
  void SetPacketSequenceNumber (uint16_t seqnum)
  {
    m_packetSequenceNumber = seqnum;
  }

  /**
   * Get the packet sequence number.
   * \returns The packet sequence number.
   */
  uint16_t GetPacketSequenceNumber () const
  {
    return m_packetSequenceNumber;
  }

private:
  uint16_t m_packetLength;          //!< The packet length.
  uint16_t m_packetSequenceNumber;  //!< The packet sequence number.

public:
  /**
   * \brief Get the type ID.
   * \return The object TypeId.
   */
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
};


// class DataPacketHeader : public Header
// {
// public:
//   DataPacketHeader ();
//   virtual ~DataPacketHeader ();

//   void SetNextJID(uint8_t jid)
//   {
//       nextjid = jid;
//   }

//   uint8_t GetNextJID() const
//   {
//       return nextjid;
//   }

//   void SetSenderID(int id)
//   {
//       sender = id;
//   }

//   int GetSenderID() const
//   {
//       return sender;
//   }

// private:
//   uint8_t nextjid;
//   uint16_t sender;


// public:
//   static TypeId GetTypeId (void);
//   virtual TypeId GetInstanceTypeId (void) const;
//   virtual void Print (std::ostream &os) const;
//   virtual uint32_t GetSerializedSize (void) const;
//   virtual void Serialize (Buffer::Iterator start) const;
//   virtual uint32_t Deserialize (Buffer::Iterator start);
// };

class DataPacketHeader : public Header
{
public:
  DataPacketHeader ();
  virtual ~DataPacketHeader ();
  uint16_t next_jid_idx = 0;
  std::vector<uint16_t> path;


public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
};
//	  0                   1                   2                   3
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |  Message Type |     Vtime     |         Message Size          |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                      Originator Address                       |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |  Time To Live |   Hop Count   |    Message Sequence Number    |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                                                               |
//   :                            MESSAGE                            :
//   |                                                               |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

class MessageHeader : public Header
{
public:
  enum MessageType
  {
	HELLO_MESSAGE = 1,
  CPACK_MESSAGE = 2,
    ANT_MESSAGE,
  };

  MessageHeader ();
  virtual ~MessageHeader ();

  void SetMessageType (MessageType messageType)
  {
	m_messageType = messageType;
  }

  MessageType GetMessageType () const
  {
	return m_messageType;
  }

  void SetVTime (Time time)
  {
	m_vTime = SecondsToEmf (time.GetSeconds ());
  }

  Time GetVTime () const
  {
	return Seconds (EmfToSeconds (m_vTime));
  }

  void SetOriginatorAddress (Ipv4Address originatorAddress)
  {
	m_originatorAddress = originatorAddress;
  }

  Ipv4Address GetOriginatorAddress () const
  {
	return m_originatorAddress;
  }

  void SetTimeToLive (uint8_t timeToLive)
  {
	m_timeToLive = timeToLive;
  }

  uint8_t GetTimeToLive () const
  {
	return m_timeToLive;
  }

  void SetHopCount (uint8_t hopCount)
  {
	m_hopCount = hopCount;
  }

  uint8_t GetHopCount () const
  {
	return m_hopCount;
  }

  void SetMessageSequenceNumber (uint16_t messageSequenceNumber)
  {
	m_messageSequenceNumber = messageSequenceNumber;
  }

  uint16_t GetMessageSequenceNumber () const
  {
	return m_messageSequenceNumber;
  }

private:
  MessageType m_messageType;
  uint8_t m_vTime;
  Ipv4Address m_originatorAddress;
  uint8_t m_timeToLive;
  uint8_t m_hopCount;
  uint16_t m_messageSequenceNumber;
  uint16_t m_messageSize;

public:
  /**
   * \brief Get the type ID.
   * \return The object TypeId.
   */
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);

//   --------------------------HELLO MESSAGE--------------------------
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                           Location X                          |
//   |                                                               |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                           Location Y                          |
//   |                                                               |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                             speed                             |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                           direction                           |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                        Neighbor Address                       |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                        Neighbor Address                       |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                              ...                              |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    struct Hello
    {
        uint64_t locationX;
        uint64_t locationY;
        uint32_t speed;
        uint32_t direction;
        uint16_t turn;

        // int bsize = 0;
        // int asize = 0;

        // int GetBeaconSize() const
        // {
        //     return bsize;
        // }

        // int GetBeaconAppendSize() const
        // {
        //     return asize;
        // }

        // std::vector<JunInfo> conlist;

        void SetTurn(int njid)
        {
            this->turn = (uint16_t)njid;
        }

        void SetLocation(double x, double y)
        {
            this->locationX = LocToUint64((uint64_t)(x * 1000));
            this->locationY = LocToUint64((uint64_t)(y * 1000));
        }

        void SetSpeedAndDirection(double speed, uint32_t direction)
        {
            this->speed = (uint32_t)(speed * 1000);
            this->direction = direction;
        }

        int GetTurn() const
        {
            if(this->turn >= 1000)
                return -1;
            else
                return (int)this->turn;
        }

        double GetLocationX() const
        {
            return Uint64ToLoc(this->locationX) / 1000.0;
        }

        double GetLocationY() const
        {
            return Uint64ToLoc(this->locationY) / 1000.0;
        }

        double GetSpeed() const
        {
            return double(this->speed) / 1000.0;
        }

        uint32_t GetDirection() const
        {
        return this->direction;
        }

        std::vector<Ipv4Address> neighborInterfaceAddresses;

        void Print (std::ostream &os) const;
        uint32_t GetSerializedSize (void) const;
        void Serialize (Buffer::Iterator start) const;
        uint32_t Deserialize (Buffer::Iterator start, uint32_t messageSize);
        
    };

    struct Ant{
        Ipv4Address sender_addr;
        uint16_t seq_num;
        uint16_t version;
        uint16_t jun_from;
        uint16_t next_junction_id;
        std::vector<uint16_t> sequence_of_junctions;
        std::vector<Time> s_delay;
        Ipv4Address next_forwarder;
        Ipv4Address last_sender;
        float last_sender_position_x;
        
        float last_sender_position_y;
        uint32_t GetSerializedSize (void) const;
        void Serialize (Buffer::Iterator start) const;
        uint32_t Deserialize (Buffer::Iterator start, uint32_t messageSize);


    };

private:
  struct
  {
    Hello hello;
    Ant ant;
  } m_message;

public:
  MessageHeader(MessageType type):m_messageType(type){

  }
  Hello& GetHello ()
  {
    if (m_messageType == 0)
      {
        m_messageType = HELLO_MESSAGE;
      }
    // else
    //   {
    //     NS_ASSERT (m_messageType == HELLO_MESSAGE);
    //   }
    return m_message.hello;
  }

  Ant& GetAnt()
  {
    if (m_messageType == 0)
      {
        m_messageType = ANT_MESSAGE;
      }
    // else
    //   {
    //     NS_ASSERT (m_messageType == ANT_MESSAGE);
    //   }
    return m_message.ant;
  }

  const Ant& GetAnt() const{
      return m_message.ant;
  }
                
  const Hello& GetHello () const
  {
    // NS_ASSERT (m_messageType == HELLO_MESSAGE);
    return m_message.hello;
  }
};

static inline std::ostream& operator<< (std::ostream& os, const MessageHeader & message)
{
  message.Print (os);
  return os;
}

typedef std::vector<MessageHeader> MessageList;

static inline std::ostream& operator<< (std::ostream& os, const MessageList & messages)
{
  os << "[";
  for (std::vector<MessageHeader>::const_iterator messageIter = messages.begin ();
       messageIter != messages.end (); messageIter++)
    {
      messageIter->Print (os);
      if (messageIter + 1 != messages.end ())
        {
          os << ", ";
        }
    }
  os << "]";
  return os;
}


}
}

#endif /* GRP_HEADER_H */


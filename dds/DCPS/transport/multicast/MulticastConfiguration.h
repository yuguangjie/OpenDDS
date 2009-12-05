/*
 * $Id$
 *
 * Copyright 2009 Object Computing, Inc.
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef DCPS_MULTICASTCONFIGURATION_H
#define DCPS_MULTICASTCONFIGURATION_H

#include "Multicast_Export.h"

#include "ace/INET_Addr.h"
#include "ace/Time_Value.h"

#include "dds/DCPS/transport/framework/TransportConfiguration.h"

namespace OpenDDS {
namespace DCPS {

// The default Transport ID forces the group address selection
// heuristic to resolve port number 49152; this is the minimal
// port defined in the dynamic/private range [IANA 2009-11-16].
const TransportIdType DEFAULT_MULTICAST_ID(0xFFFFFF08);

class OpenDDS_Multicast_Export MulticastConfiguration
  : public TransportConfiguration {
public:
  /// Enable/disable IPv6 default group address selection.
  /// The default value is: false.
  bool default_to_ipv6_;

  /// The offset used to determine default port numbers;
  /// this value will be added to the Transport ID.
  /// The default value is: 49400 [IANA 2009-11-16].
  u_short port_offset_;

  /// The multicast group to join.
  /// The default value is:
  ///   224.0.0.128:<port> [IANA 2009-11-17], and
  ///    [FF01::80]:<port> [IANA 2009-08-28] 
  ACE_INET_Addr group_address_;

  /// Enable/disable reliable communication. This option
  /// will eventually be deprecated once the ETF is able
  /// to properly demux reliable/best-effort samples.
  /// The default value is: true.
  bool reliable_;

  /// The maximum number of milliseconds to wait between
  /// handshake attempts during association (reliable only).
  /// The default value is: 500.
  ACE_Time_Value syn_interval_;

  /// The maximum number of milliseconds to wait for a
  /// handshake response during association (reliable only).
  /// The default value is: 30000 (30 seconds).
  ACE_Time_Value syn_timeout_;

  /// The number of datagrams to retain in order to service
  /// service incoming repair requests (reliable only).
  /// The default value is: 32; this yields a minimum of 32
  /// samples and a maximum 2048K of sample data.
  size_t nak_depth_;

  /// The maximum number of milliseconds to wait between
  /// repair requests (reliable only).
  /// The default value is: 2000 (2 seconds).
  ACE_Time_Value nak_interval_;

  /// The maximum number of milliseconds to wait before
  /// giving up on a repair response (reliable only).
  /// The default value is: 30000 (30 seconds).
  ACE_Time_Value nak_timeout_;

  MulticastConfiguration();

  virtual int load(const TransportIdType& id,
                   ACE_Configuration_Heap& config);

private:
  void default_group_address(ACE_INET_Addr& group_address,
                             const TransportIdType& id);
};

} // namespace DCPS
} // namespace OpenDDS

#endif  /* DCPS_MULTICASTCONFIGURATION_H */

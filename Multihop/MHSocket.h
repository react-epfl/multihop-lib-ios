//
//  MHSocket.h
//  Multihop
//
//  Created by quarta on 02/06/15.
//  Copyright (c) 2015 quarta. All rights reserved.
//

#ifndef Multihop_MHSocket_h
#define Multihop_MHSocket_h


#import <Foundation/Foundation.h>
#import "MHController.h"


@protocol MHSocketDelegate;

@interface MHSocket : NSObject

#pragma mark - Properties

/// Delegate for the MHMultihop methods
@property (nonatomic, weak) id<MHSocketDelegate> delegate;


#pragma mark - Initialization

/**
 Init method for this class.
 
 Since you are not passing in a display name, it will default to:
 
 [UIDevice currentDevice].name]
 
 Since you are not passing a routing protocol, the default one will be Flooding
 
 Which returns a string similar to: @"Peter's iPhone".
 
 @param serviceType The type of service to advertise. This should be a short text string that describes the app's networking protocol, in the same format as a Bonjour service type:
 
 1. Must be 1–13 characters long.
 2. Can contain only ASCII lowercase letters, numbers, and hyphens.
 
 This name should be easily distinguished from unrelated services. For example, a text chat app made by ABC company could use the service type abc-txtchat. For more details, read “Domain Naming Conventions”.
 */
- (instancetype)initWithServiceType:(NSString *)serviceType;

/**
 Init method for this class.
 
 Since you are not passing in a display name, it will default to:
 
 [UIDevice currentDevice].name]
 
 @param serviceType The type of service to advertise. This should be a short text string that describes the app's networking protocol, in the same format as a Bonjour service type:
 
 1. Must be 1–13 characters long.
 2. Can contain only ASCII lowercase letters, numbers, and hyphens.
 
 This name should be easily distinguished from unrelated services. For example, a text chat app made by ABC company could use the service type abc-txtchat. For more details, read “Domain Naming Conventions”.
 
 
 @param protocol The routing protocol used.
 */
- (instancetype)initWithServiceType:(NSString *)serviceType
                withRoutingProtocol:(MHRoutingProtocols)protocol;

/**
 Init method for this class.
 
 @param serviceType The type of service to advertise. This should be a short text string that describes the app's networking protocol, in the same format as a Bonjour service type:
 
 1. Must be 1–13 characters long.
 2. Can contain only ASCII lowercase letters, numbers, and hyphens.
 
 This name should be easily distinguished from unrelated services. For example, a text chat app made by ABC company could use the service type abc-txtchat. For more details, read “Domain Naming Conventions”.
 
 @param displayName The display name which is sent to other peers.
 
 @param protocol The routing protocol used.
 */
- (instancetype)initWithServiceType:(NSString *)serviceType
                        displayName:(NSString *)displayName
                withRoutingProtocol:(MHRoutingProtocols)protocol;


/**
 Call this method to disconnect from everyone. In order to restart the system, a new Multihop object
 should be reinstantiated.
 */
- (void)disconnect;

/**
 Call this method to join a multicast group
 
 @param groupName The name of the group to join
 */
- (void)joinGroup:(NSString *)groupName;


/**
 Call this method to leave a multicast group
 
 @param groupName The name of the group to leave
 */
- (void)leaveGroup:(NSString *)groupName;


/**
 Sends a message to selected groups.
 
 They will receive the data with the delegate callback:
 
 - (void)mhSocket:(MHSocket *)mhSocket didReceiveMessage:(NSData *)data fromPeer:(NSString *)peer
 
 @param data message data to send.
 @param destinations list of multicast groups to which send the message
 @param error The address of an NSError pointer where an error object should be stored upon error.
 
 */
- (void)sendMessage:(NSData *)data
     toDestinations:(NSArray *)destinations
              error:(NSError **)error;

/**
 Return the current peer id
 */
- (NSString *)getOwnPeer;

/**
 Returns the number of hops from a particular peer
 
 @param peer the peer id
 */
- (int)hopsCountFromPeer:(NSString*)peer;



// Background Mode methods
- (void)applicationWillResignActive;

- (void)applicationDidBecomeActive;

// Termination method
- (void)applicationWillTerminate;




@end

/**
 The delegate for the MHSocket class.
 */
@protocol MHSocketDelegate <NSObject>

@required
- (void)mhSocket:(MHSocket *)mhSocket
 failedToConnect:(NSError *)error;

- (void)mhSocket:(MHSocket *)mhSocket
didReceiveMessage:(NSData *)data
        fromPeer:(NSString *)peer
   withTraceInfo:(NSArray *)traceInfo;

@optional

#pragma mark - Diagnostics info callbacks
- (void)mhSocket:(MHSocket *)mhSocket
   forwardPacket:(NSString *)info
     withMessage:(NSData *)message
      fromSource:(NSString *)peer;

- (void)mhSocket:(MHSocket *)mhSocket
neighbourConnected:(NSString *)info
            peer:(NSString *)peer
     displayName:(NSString *)displayName;

- (void)mhSocket:(MHSocket *)mhSocket
neighbourDisconnected:(NSString *)info
            peer:(NSString *)peer;

- (void)mhSocket:(MHSocket *)mhSocket
     joinedGroup:(NSString *)info
            peer:(NSString *)peer
     displayName:(NSString *)displayName
           group:(NSString *)group;
@end

#endif
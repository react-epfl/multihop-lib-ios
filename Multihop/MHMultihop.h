//
//  MHMultihop.h
//  Multihop
//
//  Created by quarta on 24/03/15.
//  Copyright (c) 2015 quarta. All rights reserved.
//

#ifndef Multihop_MHMultihop_h
#define Multihop_MHMultihop_h

#import <Foundation/Foundation.h>
#import <MultipeerConnectivity/MultipeerConnectivity.h>
#import "MHConnectionsHandler.h"
#import "MHBackgroundManager.h"


@protocol MHMultihopDelegate;

@interface MHMultihop : NSObject

#pragma mark - Properties

/// Delegate for the MHMultihop methods
@property (nonatomic, weak) id<MHMultihopDelegate> delegate;


#pragma mark - Initialization

/**
 Init method for this class.
 
 You must initialize this method with this method or:
 
 - (instancetype)initWithServiceType:(NSString *)serviceType displayName:(NSString *)displayName;
 
 Since you are not passing in a display name, it will default to:
 
 [UIDevice currentDevice].name]
 
 Which returns a string similar to: @"Peter's iPhone".
 
 @param serviceType The type of service to advertise. This should be a short text string that describes the app's networking protocol, in the same format as a Bonjour service type:
 
 1. Must be 1–15 characters long.
 2. Can contain only ASCII lowercase letters, numbers, and hyphens.
 
 This name should be easily distinguished from unrelated services. For example, a text chat app made by ABC company could use the service type abc-txtchat. For more details, read “Domain Naming Conventions”.
 */
- (instancetype)initWithServiceType:(NSString *)serviceType;

/**
 Init method for this class.
 
 You must initialize this method with this method or:
 
 - (instancetype)initWithServiceType:(NSString *)serviceType;
 
 @param serviceType The type of service to advertise. This should be a short text string that describes the app's networking protocol, in the same format as a Bonjour service type:
 
 1. Must be 1–15 characters long.
 2. Can contain only ASCII lowercase letters, numbers, and hyphens.
 
 This name should be easily distinguished from unrelated services. For example, a text chat app made by ABC company could use the service type abc-txtchat. For more details, read “Domain Naming Conventions”.
 
 @param displayName The display name which is sent to other peers.
 */
- (instancetype)initWithServiceType:(NSString *)serviceType
                        displayName:(NSString *)displayName;

/**
 Call this method to connect to all peers. It will automatically start searching for peers.
 
 When you successfully connect to another peer, you will receive a delegate callback to:
 
 - (void)mhHandler:(MHMultihop *)mhHandler hasConnected:(NSString *)info peer:(NSString *)peer displayName:(NSString *)displayName;
 */
- (void)connectToAll;


/**
 Call this method to disconnect from everyone. You can reconnect at any time using the connectToAll method.
 */
- (void)disconnectFromAll;

/**
 Broadcast data to all connected peers.
 
 They will receive the data with the delegate callback:
 
 - (void)mhHandler:(MHMultihop *)mhHandler didReceiveData:(NSData *)data fromPeer:(NSString *)peer;
 
 @param data Data to send.
 @param error The address of an NSError pointer where an error object should be stored upon error.
 
 */
- (void)sendData:(NSData *)data
           error:(NSError **)error;

/**
 Sends data to selected peers.
 
 They will receive the data with the delegate callback:
 
 - (void)mhHandler:(MHMultihop *)mhHandler didReceiveData:(NSData *)data fromPeer:(NSString *)peer;
 
 @param data Data to send.
 @param to^Peers An array of MHPeerID (strings) to send data to.
 @param error The address of an NSError pointer where an error object should be stored upon error.
 
 */
- (void)sendData:(NSData *)data
         toPeers:(NSArray *)peers
           error:(NSError **)error;

- (NSString *)getOwnPeer;




// Background Mode methods
- (void)applicationWillResignActive;

- (void)applicationDidBecomeActive;

// Termination method
- (void)applicationWillTerminate;

@end

/**
 The delegate for the MHMultihop class.
 */
@protocol MHMultihopDelegate <NSObject>

@required
- (void)mhHandler:(MHMultihop *)mhHandler
  hasDisconnected:(NSString *)info
             peer:(NSString *)peer;

- (void)mhHandler:(MHMultihop *)mhHandler
     hasConnected:(NSString *)info
             peer:(NSString *)peer
      displayName:(NSString *)displayName;

- (void)mhHandler:(MHMultihop *)mhHandler
  failedToConnect:(NSError *)error;

@optional
- (void)mhHandler:(MHMultihop *)mhHandler
   didReceiveData:(NSData *)data
         fromPeer:(NSString *)peer;
@end


#endif
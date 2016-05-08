/* Copyright (c) 1996-2014 Clickteam
*
* This source code is part of the iOS exporter for Clickteam Multimedia Fusion 2
* and Clickteam Fusion 2.5.
* 
* Permission is hereby granted to any person obtaining a legal copy 
* of Clickteam Multimedia Fusion 2 or Clickteam Fusion 2.5 to use or modify this source 
* code for debugging, optimizing, or customizing applications created with 
* Clickteam Multimedia Fusion 2 and/or Clickteam Fusion 2.5. 
* Any other use of this source code is prohibited.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/
//----------------------------------------------------------------------------------
//
// CSOUND : un echantillon
//
//----------------------------------------------------------------------------------
#import <Foundation/Foundation.h>
#import <AVFoundation/AVAudioPlayer.h>
#import <OpenAL/al.h>
#import <OpenAL/alc.h>

@class CSoundPlayer;
@class CFile;
@class CALPlayer;

#define PSOUNDFLAG_IPHONE_AUDIOPLAYER 0x0004
#define PSOUNDFLAG_IPHONE_OPENAL 0x0008

@interface CSound : NSObject <AVAudioPlayerDelegate>
{
@public 
	CFile* file;
	NSUInteger pointer;
	CSoundPlayer* soundPlayer;
    CALPlayer* ALPlayer;
	AVAudioPlayer* AVPlayer;
    short handle;
    BOOL bUninterruptible;
	BOOL bPlaying;
	BOOL bPaused;
	BOOL gamePaused;
	NSString* name;
    double volume;
    int duration;
    
    BOOL bAudioPlayer;
    ALuint bufferID;
    int nSound;
	NSTimeInterval pauseTime;

}
-(id)initWithSoundPlayer:(CSoundPlayer*)p andALPlayer:(CALPlayer*)alp;
-(void)dealloc;
-(void)load:(CFile*)file flags:(short)flags;
-(void)play:(int)nLoops channel:(int)channel;
-(void)pause:(BOOL)gamePause;
-(BOOL)isPaused;
-(void)resume:(BOOL)gameResume;
-(void)stop;
-(void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;
-(void)audioPlayerBeginInterruption:(AVAudioPlayer*)player;
-(void)audioPlayerEndInterruption:(AVAudioPlayer *)player;
-(void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer*)player error:(NSError*)error;
-(void)setVolume:(int)v;
-(int)getVolume;
-(void)setPosition:(int)p;
-(int)getPosition;
-(int)getDuration;
-(void)cleanMemory;
-(void)checkPlaying;
-(void)setPitch:(float)p;

@end

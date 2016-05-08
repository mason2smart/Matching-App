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
// CEXTLOAD Chargement des extensions
//
//----------------------------------------------------------------------------------
#import "CExtLoad.h"
#import "CFile.h"
#import "CRunExtension.h"

//F01
#import "CRunKcBoxA.h"
#import "CRunkcedit.h"
#import "CRunLayer.h"
#import "CRunMultipleTouch.h"
//F01END

@implementation CExtLoad

-(void)dealloc
{
	[name release];
	[subType release];
	[super dealloc];
}
-(void)loadInfo:(CFile*)file
{
	NSUInteger debut = [file getFilePointer];
	
	short size = abs([file readAShort]);
	handle = [file readAShort];
	[file skipBytes:12];
	
	name = [file readAString];
	NSRange index = [name rangeOfString:@"."];
	if (index.location!=NSNotFound)
	{
		NSString* temp=[name substringToIndex:index.location];
		[name release];
		name=temp;
		[name retain];
	}
	subType = [file readAString];
	
	[file seek:debut + size];
}

-(CRunExtension*)loadRunObject 
{
	CRunExtension* object=nil;
	
//F02 			
	
if ([name caseInsensitiveCompare:@"KcBoxA"]==0)
{
object=[[CRunKcBoxA alloc] init];
}

if ([name caseInsensitiveCompare:@"kcedit"]==0)
{
object=[[CRunkcedit alloc] init];
}

if ([name caseInsensitiveCompare:@"Layer"]==0)
{
object=[[CRunLayer alloc] init];
}

if ([name caseInsensitiveCompare:@"MultipleTouch"]==0)
{
object=[[CRunMultipleTouch alloc] init];
}
//F02END
	
	return object;
}

@end

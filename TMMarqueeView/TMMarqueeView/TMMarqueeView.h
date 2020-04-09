//
//  TMMarqueeView.h
//  TMMarqueeView
//
//  Created by Luther on 2020/4/9.
//  Copyright © 2020 mrstock. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class TMMarqueeView;

typedef NS_ENUM(NSUInteger, TMMarqueeViewDirection) {
    TMMarqueeViewDirectionUp,       //向上滚动
    TMMarqueeViewDirectionLeft,     //向左滚动
};

#pragma mark - TMMarqueeViewDelegate
@protocol TMMarqueeViewDelegate <NSObject>
- (NSUInteger)numberOfDataForMarqueeView:(TMMarqueeView*)marqueeView;
- (void)createItemView:(UIView*)itemView forMarqueeView:(TMMarqueeView*)marqueeView;
- (void)updateItemView:(UIView*)itemView atIndex:(NSUInteger)index forMarqueeView:(TMMarqueeView*)marqueeView;
@optional
- (NSUInteger)numberOfVisibleItemsForMarqueeView:(TMMarqueeView*)marqueeView;   // only for [TMMarqueeViewDirectionUpward]
- (CGFloat)itemViewWidthAtIndex:(NSUInteger)index forMarqueeView:(TMMarqueeView*)marqueeView;   // only for [TMMarqueeViewDirectionLeftward]
- (CGFloat)itemViewHeightAtIndex:(NSUInteger)index forMarqueeView:(TMMarqueeView*)marqueeView;   // only for [TMMarqueeViewDirectionUpward] and [useDynamicHeight = YES]
- (void)didTouchItemViewAtIndex:(NSUInteger)index forMarqueeView:(TMMarqueeView*)marqueeView;
@end

@interface TMMarqueeView : UIView

@property (nonatomic, weak) id <TMMarqueeViewDelegate> delegate;

/// 滚动的间隔时间(定时器设置的时间), 默认是4s.
@property (nonatomic, assign) NSTimeInterval timeIntervalPerScroll;
/// 滚动的动画时间, 默认是1s.
/// 只用在(direction=TMMarqueeViewDirectionUp & useDynamicHeight=NO)
@property (nonatomic, assign) NSTimeInterval timeDurationPerScroll;
/// 是否使用人为设置的item高度, 默认是NO.
/// 只用在(direction=TMMarqueeViewDirectionUp)
@property (nonatomic, assign) BOOL useDynamicHeight;
/// 滚动速度, 默认是40.0f.
/// 只用在(direction=TMMarqueeViewDirectionUp & useDynamicHeight=YES)
/// 或者(direction=TMMarqueeViewDirectionLeft)
@property (nonatomic, assign) CGFloat scrollSpeed;
/// item的间隔, 默认是20.0f.
/// 只用在(direction=TMMarqueeViewDirectionLeft)
@property (nonatomic, assign) CGFloat itemSpacing;
/// 当item全部在视图中显示时,是否不在滚动.
@property (nonatomic, assign) BOOL stopWhenLessData;
@property (nonatomic, assign) BOOL clipsToBounds;
/// 是否可点击
@property (nonatomic, assign, getter=isTouchEnabled) BOOL touchEnabled;
/// 滚动的方向
@property (nonatomic, assign) TMMarqueeViewDirection direction;

- (instancetype)initWithDirection:(TMMarqueeViewDirection)direction;
- (instancetype)initWithFrame:(CGRect)frame direction:(TMMarqueeViewDirection)direction;
- (void)reloadData;
- (void)start;
- (void)pause;

@end

#pragma mark - TMMarqueeViewTouchResponder(Private)
@protocol TMMarqueeViewTouchResponder <NSObject>
- (void)touchesBegan;
- (void)touchesEndedAtPoint:(CGPoint)point;
- (void)touchesCancelled;
@end

#pragma mark - TMMarqueeViewTouchReceiver(Private)
@interface TMMarqueeViewTouchReceiver : UIView
@property (nonatomic, weak) id<TMMarqueeViewTouchResponder> touchDelegate;
@end

@interface TMMarqueeItemView : UIView
@property (nonatomic, assign) BOOL didFinishCreate;
@property (nonatomic, assign) CGFloat width;
@property (nonatomic, assign) CGFloat height;
- (void)clear;
@end

NS_ASSUME_NONNULL_END

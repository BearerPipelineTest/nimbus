//
// Copyright 2011-2014 NimbusKit
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>

#import "NICollectionViewModel.h"

API_DEPRECATED_BEGIN("Follow go/material-ios-lists for list guidance instead.",
                     ios(12, API_TO_BE_DEPRECATED))

@interface NICollectionViewModelSection : NSObject

+ (id)section;

@property (nonatomic, copy) NSString* headerTitle;
@property (nonatomic, copy) NSString* footerTitle;
@property (nonatomic, strong) NSArray* rows;

@end

@interface NICollectionViewModel()

@property (nonatomic, strong) NSArray* sections; // Array of NICollectionViewModelSection
@property (nonatomic, strong) NSArray* sectionIndexTitles;
@property (nonatomic, strong) NSDictionary* sectionPrefixToSectionIndex;

- (void)_resetCompiledData;
- (void)_compileDataWithListArray:(NSArray *)listArray;
- (void)_compileDataWithSectionedArray:(NSArray *)sectionedArray;
- (void)_setSectionsWithArray:(NSArray *)sectionsArray;
- (NICollectionViewModelSection *)_sectionFromListArray:(NSArray *)rows;

@end

API_DEPRECATED_END

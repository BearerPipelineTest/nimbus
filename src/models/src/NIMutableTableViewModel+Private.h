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

#import "NIMutableTableViewModel.h"
#import "NITableViewModel+Private.h"

API_DEPRECATED_BEGIN("Follow go/material-ios-lists for list guidance instead.",
                     ios(12, API_TO_BE_DEPRECATED))

@interface NIMutableTableViewModel (Private)

@property (nonatomic, strong) NSMutableArray* sections; // Array of NITableViewModelSection
@property (nonatomic, strong) NSMutableArray* sectionIndexTitles;
@property (nonatomic, strong) NSMutableDictionary* sectionPrefixToSectionIndex;

@end

@interface NITableViewModelSection (Mutable)

- (NSMutableArray *)mutableRows;

@end

API_DEPRECATED_END

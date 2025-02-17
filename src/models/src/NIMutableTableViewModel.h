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

#import "NITableViewModel.h"

API_DEPRECATED_BEGIN("Follow go/material-ios-lists for list guidance instead.",
                     ios(12, API_TO_BE_DEPRECATED))

@class NIMutableTableViewModel;

/**
 * A protocol for NIMutableTableViewModel to handle editing states for objects.
 *
 * @ingroup TableViewModels
 */
@protocol NIMutableTableViewModelDelegate <NSObject, NITableViewModelDelegate>

@optional

/**
 * Asks the receiver whether the object at the given index path should be editable.
 *
 * If this method is not implemented, the default response is assumed to be NO.
 */
- (BOOL)tableViewModel:(nonnull NIMutableTableViewModel *)tableViewModel
         canEditObject:(nonnull id)object
           atIndexPath:(nonnull NSIndexPath *)indexPath
           inTableView:(nonnull UITableView *)tableView;

/**
 * Asks the receiver whether the object at the given index path should be moveable.
 *
 * If this method is not implemented, the default response is assumed to be NO.
 */
- (BOOL)tableViewModel:(nonnull NIMutableTableViewModel *)tableViewModel
         canMoveObject:(nonnull id)object
           atIndexPath:(nonnull NSIndexPath *)indexPath
           inTableView:(nonnull UITableView *)tableView;

/**
 * Asks the receiver whether the given object should be moved.
 *
 * If this method is not implemented, the default response is assumed to be YES.
 *
 * Returning NO will stop the model from handling the move logic.
 */
- (BOOL)tableViewModel:(nonnull NIMutableTableViewModel *)tableViewModel
      shouldMoveObject:(nonnull id)object
           atIndexPath:(nonnull NSIndexPath *)indexPath
           toIndexPath:(nonnull NSIndexPath *)toIndexPath
           inTableView:(nonnull UITableView *)tableView;

/**
 * Asks the receiver what animation should be used when deleting the object at the given index path.
 *
 * If this method is not implemented, the default response is assumed to be
 * UITableViewRowAnimationAutomatic.
 */
- (UITableViewRowAnimation)tableViewModel:(nonnull NIMutableTableViewModel *)tableViewModel
              deleteRowAnimationForObject:(nonnull id)object
                              atIndexPath:(nonnull NSIndexPath *)indexPath
                              inTableView:(nonnull UITableView *)tableView;

/**
 * Asks the receiver whether the given object should be deleted.
 *
 * If this method is not implemented, the default response is assumed to be YES.
 *
 * Returning NO will stop the model from handling the deletion logic. This is a good opportunity for
 * you to show a UIAlertView or similar feedback prompt to the user before initiating the deletion
 * yourself.
 *
 * If you implement the deletion of the object yourself, your code may resemble the following:
@code
NSArray *indexPaths = [self removeObjectAtIndexPath:indexPath];
[tableView deleteRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
@endcode
 */
- (BOOL)tableViewModel:(nonnull NIMutableTableViewModel *)tableViewModel
    shouldDeleteObject:(nonnull id)object
           atIndexPath:(nonnull NSIndexPath *)indexPath
           inTableView:(nonnull UITableView *)tableView;

@end

/**
 * The NIMutableTableViewModel class is a mutable table view model.
 *
 * When modifications are made to the model there are two ways to reflect the changes in the table
 * view.
 *
 * - Call reloadData on the table view. This is the most destructive way to update the table view.
 * - Call insert/delete/reload methods on the table view with the retuned index path arrays.
 *
 * The latter option is the recommended approach to adding new cells to a table view. Each method in
 * the mutable table view model returns a data structure that can be used to inform the table view
 * of the exact modifications that have been made to the model.
 *
 * Example of adding a new section:
@code
// Appends a new section to the end of the model.
NSIndexSet* indexSet = [self.model addSectionWithTitle:@"New section"];

// Appends a cell to the last section in the model (in this case, the new section we just created).
[self.model addObject:[NITitleCellObject objectWithTitle:@"A cell"]];

// Inform the table view that we've modified the model.
[self.tableView insertSections:indexSet withRowAnimation:UITableViewRowAnimationAutomatic];
@endcode
 *
 * @ingroup TableViewModels
 */
@interface NIMutableTableViewModel : NITableViewModel

- (nonnull NSArray *)addObject:(nonnull id)object;
- (nonnull NSArray *)addObject:(nonnull id)object toSection:(NSUInteger)section;
- (nonnull NSArray *)addObjectsFromArray:(nonnull NSArray *)array;
- (nonnull NSArray *)insertObject:(nonnull id)object atRow:(NSUInteger)row inSection:(NSUInteger)section;
- (nonnull NSArray *)removeObjectAtIndexPath:(nonnull NSIndexPath *)indexPath;

- (nonnull NSIndexSet *)addSectionWithTitle:(nonnull NSString *)title;
- (nonnull NSIndexSet *)insertSectionWithTitle:(nonnull NSString *)title atIndex:(NSUInteger)index;
- (nonnull NSIndexSet *)removeSectionAtIndex:(NSUInteger)index;

- (void)updateSectionIndex;

@property (nonatomic, weak, nullable) id<NIMutableTableViewModelDelegate> delegate;

@end

/** @name Modifying Objects */

/**
 * Appends an object to the last section.
 *
 * If no sections exist, a section will be created without a title and the object will be added to
 * this new section.
 *
 * @param object The object to append to the last section.
 * @returns An array with a single NSIndexPath representing the index path of the new object
 *               in the model.
 * @fn NIMutableTableViewModel::addObject:
 */

/**
 * Appends an object to the end of the given section.
 *
 * @param object The object to append to the section.
 * @param section The index of the section to which this object should be appended.
 * @returns An array with a single NSIndexPath representing the index path of the new object
 *               in the model.
 * @fn NIMutableTableViewModel::addObject:toSection:
 */

/**
 * Appends an array of objects to the last section.
 *
 * If no section exists, a section will be created without a title and the objects will be added to
 * this new section.
 *
 * @param array The array of objects to append to the last section.
 * @returns An array of NSIndexPath objects representing the index paths of the objects in the
 *               model.
 * @fn NIMutableTableViewModel::addObjectsFromArray:
 */

/**
 * Inserts an object into the given section at the given row.
 *
 * @param object The object to append to the section.
 * @param row The row within the section at which to insert the object.
 * @param section The index of the section in which the object should be inserted.
 * @returns An array with a single NSIndexPath representing the index path of the new object
 *               in the model.
 * @fn NIMutableTableViewModel::insertObject:atRow:inSection:
 */

/**
 * Removes an object at the given index path.
 *
 * If the index path does not represent a valid object then a debug assertion will fire and the
 * method will return nil without removing any object.
 *
 * @param indexPath The index path at which to remove a single object.
 * @returns An array with a single NSIndexPath representing the index path of the object that
 *               was removed from the model, or nil if no object exists at the given index path.
 * @fn NIMutableTableViewModel::removeObjectAtIndexPath:
 */

/** @name Modifying Sections */

/**
 * Appends a section with a given title to the model.
 *
 * @param title The title of the new section.
 * @returns An index set with a single index representing the index of the new section.
 * @fn NIMutableTableViewModel::addSectionWithTitle:
 */

/**
 * Inserts a section with a given title to the model at the given index.
 *
 * @param title The title of the new section.
 * @param index The index in the model at which to add the new section.
 * @returns An index set with a single index representing the index of the new section.
 * @fn NIMutableTableViewModel::insertSectionWithTitle:atIndex:
 */

/**
 * Removes a section at the given index.
 *
 * @param index The index in the model of the section to remove.
 * @returns An index set with a single index representing the index of the removed section.
 * @fn NIMutableTableViewModel::removeSectionAtIndex:
 */

/** @name Updating the Section Index */

/**
 * Updates the section index with the current section index settings.
 *
 * This method should be called after modifying the model if a section index is being used.
 *
 * @fn NIMutableTableViewModel::updateSectionIndex
 */

API_DEPRECATED_END

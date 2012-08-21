<?php

// $Id$
/**
 * @file
 * Menu enhancement admin pages.
 * 
 * The admin pages provide access to view, edit, add, and delete custom menus.
 */

/**
 * Provides an overview of all custom menus that have been created and edit/deletion options for each.
 */
function menu_enhancement_admin_main() {  
  $menus = menu_enhancement_custom_menu_load();
  $output = '';
  
  if (!empty($menus)) {
    $header = array(t('Name'), t('Menu Used'), t('Operations'));
    foreach ($menus as $menu) {
      $rows[] = array(
        array('data' => $menu->name, 'valign' => 'top'),
        array('data' => $menu->settings['use_menu'], 'valign' => 'top'),
        array('data' =>
          l(t('edit'), 'admin/config/user-interface/menu_enhancement/edit/' . urlencode($menu->name)) . ' ' .
          l(t('delete'), 'admin/config/user-interface/menu_enhancement/delete/' . urlencode($menu->name)), 'valign' => 'top'
        )
      );
    }
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }
  else {
    drupal_set_message(t('There are currently no custom menus . Add a new one using the link below.'));
  }
  
  $output .= '<ul>';
  $output .= '<li>' . l(t('add new custom new'), 'admin/config/user-interface/menu_enhancement/add') . '</li>';
  $output .= '</ul>';
  
  return $output;
}

/**
 * Form for adding a new custom menu.
 */
function menu_enhancement_admin_menu_form($form, $form_state, $menu = NULL) {
  global $theme;
  
  if ($menu != NULL) {
    $form['_menu'] = array(
      '#type' => 'value',
      '#value' => $menu,
    );
  }
  else {
    $menu = new stdClass();
  }

  // General settings.
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic setup'),
    '#collapsible' => FALSE,
  );
  
  $form['general']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom menu name'),
    '#default_value' => !empty($menu->name) ? $menu->name : '',
    '#maxlength' => 128,
    '#description' => t('Enter a name for this custom menu. This name is only visible within the menu enhancement administration page.'),
    '#required' => TRUE,
  );
  
  $form['general']['use_menu'] = array(
    '#type' => 'select',
    '#title' => 'Menu',
    '#default_value' => !empty($menu->settings['use_menu']) ? $menu->settings['use_menu'] : '',
    '#options' => menu_get_menus(),
    '#multiple' => FALSE,
    '#description' => t('Choose the Drupal menu you would like to get the links from for this custom menu.'),
    '#required' => TRUE,
  );
  
  // List attributes.  
  $form['list_attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('List attributes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['list_attributes']['start_depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Starting Depth'),
    '#default_value' => !empty($menu->settings['start_depth']) ? $menu->settings['start_depth'] : 0,
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t("The depth into a menu you'd like to start at."),
    '#required' => TRUE,
  );
  
  $form['list_attributes']['max_depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Depth'),
    '#default_value' => !empty($menu->settings['max_depth']) ? $menu->settings['max_depth'] : '',
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The maximum number of levels to go into the menu. Only needs to be defined if you are planning on enabling "Show children" for parent or child attributes.'),
  );
  
  $form['list_attributes']['show_parents'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of parents:'),
    '#default_value' => !empty($menu->settings['show_parents']),
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t("Indicate the level of parents to show in the active trail. Must be less than or equal to start depth. Leave blank to not show parents."),
  );
  
  $form['list_attributes']['show_children'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show children'),
    '#default_value' => !empty($menu->settings['show_children']),    
    '#description' => t('Include children as part of the menu system. If the menu is "expanded" then it will show the children, otherwise it will only show the children of the current active menu item.'),
  );
  
  $form['list_attributes']['list_id'] = array(
    '#type' => 'textfield',
    '#title' => t('List ID'),
    '#default_value' => !empty($menu->settings['list_id']) ? $menu->settings['list_id'] : '',
    '#maxlength' => 128,
    '#description' => t('A css ID to be added to the root &lt;ul&gt; element.'),
  );
  
  $form['list_attributes']['list_class'] = array(
    '#type' => 'textfield',
    '#title' => t('List class'),
    '#default_value' => !empty($menu->settings['list_class']) ? $menu->settings['list_class'] : '',
    '#maxlength' => 128,
    '#description' => t('A css class (or classes) to be added to the root &lt;ul&gt; element. Separate classes by spaces.'),
  );
  
  $form['list_attributes']['item_class_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Item class prefix'),
    '#default_value' => !empty($menu->settings['item_class_prefix']) ? $menu->settings['item_class_prefix'] : '',
    '#maxlength' => 128,
    '#description' => t('A prefix to add to the class of the &lt;li&gt; element.'),
  );
  
  $form['list_attributes']['separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Separator'),
    '#default_value' => !empty($menu->settings['separator']) ? $menu->settings['separator'] : '',
    '#maxlength' => 128,
    '#description' => t('A character or text that you would like to include between the &lt;li&gt; tags. For example, a pipe character.'),
  );

  // Parent attributes.
  $form['parent_attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parent atributes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['parent_attributes']['parent_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Class'),
    '#default_value' => !empty($menu->settings['parent_class']) ? $menu->settings['parent_class'] : '',
    '#maxlength' => 128,
    '#description' => t('A css class (or classes) to be added to the root &lt;ul&gt; element. Separate classes by spaces.'),
  );
  
  $form['parent_attributes']['parent_four_corners'] = array(
    '#type' => 'checkbox',
    '#title' => t('Four corners'),
    '#default_value' => !empty($menu->settings['parent_four_corners']),
    '#description' => t('If enabled, will apply four &lt;span&gt; tags to the parent.'),
  );
  
  $form['parent_attributes']['parent_span'] = array(
    '#type' => 'checkbox',
    '#title' => t('Span'),
    '#default_value' => !empty($menu->settings['parent_span']),
    '#description' => t('If enabled, will wrap add a &lt;span&gt; inside the &lt;a&gt; tag.'),
  );
  
  // Child attributes.  
  $form['child_attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Child atributes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['child_attributes']['child_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Class'),
    '#default_value' => !empty($menu->settings['child_class']) ? $menu->settings['child_class'] : '',
    '#maxlength' => 128,
    '#description' => t('A css class (or classes) to be added to the root &lt;ul&gt; element. Separate classes by spaces.'),
  );
  
  $form['child_attributes']['child_four_corners'] = array(
    '#type' => 'checkbox',
    '#title' => t('Four corners'),
    '#default_value' => !empty($menu->settings['child_four_corners']),
    '#description' => t('If enabled, will apply four &lt;span&gt; tags to the parent.')
  );
  
  $form['child_attributes']['child_span'] = array(
    '#type' => 'checkbox',
    '#title' => t('Span'),
    '#default_value' => !empty($menu->settings['child_span']),
    '#description' => t('If enabled, will wrap add a &lt;span&gt; inside the &lt;a&gt; tag.')
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * 
 */
function menu_enhancement_admin_menu_form_validate($form, &$form_state) {
  $edit = $form_state['values'];

  if (!$edit['name']) {
    form_set_error('name', t('You must provide a menu name.'));
  }
  elseif (!preg_match('/^[A-Za-z0-9_]+$/', $edit['name'])) {
    form_set_error('name', t('Enter valid menu name. Only alphanumeric and underscore characters are allowed.'));
  }
  elseif (!isset($edit['_menu']) || ($edit['_menu']->name != $edit['name'])) {
    $result = menu_enhancement_custom_menu_load($edit['name']);
    if (!empty($result)) {
      form_set_error('name', t('The menu name must be unique. A menu with this name already exists.'));
    }
  }
  
  if (!$edit['use_menu']) {
    form_set_error('use_menu', t('You must provide a Drupal menu to use.'));
  }
  
  if ($edit['start_depth'] == '') {
    form_set_error('start_depth', t('Start depth is required.'));
  }
  elseif (is_numeric($edit['start_depth'])) {
    if ($edit['start_depth'] < 0) {
      form_set_error('start_depth', t('Start depth must be greater than or equal to 0.'));
    }    
  }
  else {
    form_set_error('start_depth', t('Start depth must be a number.'));
  }
  
  if (is_numeric($edit['show_parents'])) {
    if ($edit['show_parents'] > $edit['start_depth']) {
      form_set_error('show_parents', t('Show parents must be less than or equal to the start depth.'));
    }
  }
  elseif ($edit['show_parents'] != '') {
    form_set_error('show_parents', t('Show parents must be a number or blank.'));
  }
  
  if ($edit['max_depth']) {
    if (is_numeric($edit['max_depth'])) {
      if ($edit['max_depth'] < 0) {
        form_set_error('max_depth', t('Maximum depth must be greater than or equal to 0.'));
      }
    }
    else {
      form_set_error('max_depth', t('Maximum depth must be a number.'));
    }
  }
  
  if (!empty($edit['list_id'])) {
    if (!preg_match('/^[A-Za-z0-9_\-]+$/', $edit['list_id'])) {
      form_set_error('list_id', t('Enter valid list ID. Only alphanumeric, underscore, and hypen characters are allowed.'));
    }  
  }
  
  if (!empty($edit['list_class'])) {
    if (!preg_match('/^[A-Za-z0-9_\- ]+$/', $edit['list_class'])) {
      form_set_error('list_class', t('Enter valid list class. Only alphanumeric, underscore, hyphen and space characters are allowed.'));
    }  
  }

  if (!empty($edit['item_class_prefix'])) {
    if (!preg_match('/^[A-Za-z0-9_\-]+$/', $edit['item_class_prefix'])) {
      form_set_error('item_class_prefix', t('Enter valid item class prefix. Only alphanumeric, underscore and hyphen characters are allowed.'));
    }  
  }
  
  if (!empty($edit['parent_class'])) {
    if (!preg_match('/^[A-Za-z0-9_\- ]+$/', $edit['parent_class'])) {
      form_set_error('parent_class', t('Enter valid parent class. Only alphanumeric, underscore, hyphen and space characters are allowed.'));
    }  
  }
  
  if (!empty($edit['child_class'])) {
    if (!preg_match('/^[A-Za-z0-9_\- ]+$/', $edit['child_class'])) {
      form_set_error('child_class', t('Enter valid child class. Only alphanumeric, underscore, hypen and space characters are allowed.'));
    }  
  }
}

/**
 * Form submit for a custom menu.
 */
function menu_enhancement_admin_menu_form_submit($form, &$form_state) {
  $edit = $form_state['values'];

  if (isset($edit['_menu'])) {
    menu_enhancement_menu_delete($edit['_menu']->name);
    drupal_set_message(t('Your custom menu has been updated.'));
  }
  else {
    drupal_set_message(t('Your custom menu has been created.'));
  }
  
  $settings = menu_enhancement_admin_values_to_settings($form_state['values']);
  
  db_insert('menu_enhancement_custom_menu')
    ->fields(array(
      "name" => $edit['name'],
      "settings" => $settings
    ))
    ->execute(); 
    
  $form_state['redirect'] = 'admin/config/user-interface/menu_enhancement';
}

/**
 * Converts an array of form values to a serialized array that does not
 * contain Drupal Form API values
 */
function menu_enhancement_admin_values_to_settings($values) {
  unset($values['name'], $values['input_formats'], $values['_profile'], $values['op'], $values['submit'], $values['form_build_id'], $values['form_token'], $values['form_id']);
  return serialize($values);
}

/**
 * Form builder for a profile delete
 */
function menu_enhancement_admin_delete_form($form, $form_state, $menu) {
  $form = array();
  
  $form['_menu'] = array(
    '#type' => 'value',
    '#value' => $menu,
  );
  
  $form['question'] = array(
    '#type' => 'item',
    '#markup' => t('Are you sure that you want to delete the custom menu %menu?', array('%menu' => $menu->name)),
  );
  
  $form['delete'] = array(
    '#type' => 'submit',
    '#id' => 'delete',
    '#value' => t('Delete'),
  );
  
  $form['back'] = array(
    '#type' => 'submit',
    '#id' => 'back',
    '#value' => t('Cancel'),
  );
  
  return $form;
}

/**
 * Submit form for a profile delete
 */
function menu_enhancement_admin_delete_form_submit($form, &$form_state) {
  $v = & $form_state['values'];
  
  if ($form_state['clicked_button']['#id'] == 'delete') {
    menu_enhancement_menu_delete($v['_menu']->name);
    drupal_set_message(t('Successfully deleted custom menu %menu.', array('%menu' => $v['_menu']->name)));
  }
  
  $form_state['redirect'] = 'admin/config/user-interface/menu_enhancement';
}

/**
 * Deletes a custom menu item.
 */
function menu_enhancement_menu_delete($name) {
  db_delete('menu_enhancement_custom_menu')
    ->condition('name', $name)
    ->execute();
}
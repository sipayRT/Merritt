<?php
// $Id$

/**
 * @file
 * Menu enhancement theme functions
 *
 * Functions used by menu enhancement's hook_theme functions to display custom menus on pages.
 */

/**
 * outputs the text for the menu enhancement module's help page
 */
function menu_enhancement_help_delegate($path, $arg) {
  switch ($path) {
    case 'admin/help#menu_enhancement':
      $output = '<h3>' . t('Overview') . '</h3>';
      $output .= '<p>' . t('This module provides new theming functionality when dealing with menu links. It takes the \'menu_links\' theme and provides a new theme that allows for additional parameters to be passed into the theme.') . '</p>';
      $output .= '<h3>' . t('How To Use') . '</h3>';
      $output .= '<p>' . t('When creating your template call the theme with:') . '</p>';
      $output .= '<p><em>' . t('theme(\'menu_links_enhanced\', $links, $variables);') . '</em></p>';
      $output .= '<p>' . t('$links is an array of menu links that is available from calling') . ' ' . l(t('%function', array('%function' => 'menu_tree_page_data()')), 'http://api.drupal.org/api/drupal/includes--menu.inc/function/menu_tree_page_data') . t('.');
      $output .= '<br />' . t('$attributes is an array of attribute keys => values. Below is a list of attributes and how they effect the menu display.') . '</p>';
      $output .= '<h3>' . t('Variables') . '</h3>';
      $output .= '<p>' . t('The $variables array can contain 3 associative arrays that change the output of the navigation:') . '</p>';
      $output .= '<ul>';
      $output .= '<li>';
      $output .= t('list_attributes - attributes that will be applied to the top level &lt;ul&gt; tag');
      $output .= '<ul>';
      $output .= '<li>' . t("show-parents - FALSE or a positive number to indicate the number of parents to show in the active trail. Number must be less or equal to the 'level' attribute.") . '</li>';
      $output .= '<li>' . t('show-children - TRUE / FALSE to include children as part of the menu system.<br />If the menu is "expanded" then it will show the children otherwise it only shows the children of the current selection.') . '</li>';
      $output .= '<li>' . t('level - The number of levels to go into the menu before displaying the menu') . '</li>';
      $output .= '<li>' . t('id - An id for the UL (applied only to the root menu)') . '</li>';
      $output .= '<li>' . t('class - A class to add to the UL so that it can be styled (applied only to the root menu)') . '</li>';
      $output .= '<li>' . t('item-class-prefix - A prefix to add to the class of the LI') . '</li>';
      $output .= '</ul>';
      $output .= '</li>';
      $output .= '<li>';
      $output .= t('parent_attributes - class and other attributes that will be applied to any &lt;li&gt; that has children');
      $output .= '<ul>';
      $output .= '<li>' . t('class - A class to add to the LI so that it can be styled') . '</li>';
      $output .= '<li>' . t("four_corners -> If isset it'll will apply four span's to the parent, the four spans will be called") . '</li>';
      $output .= '<li>' . t('span - if isset, it will apply a span inside the &lt;a&gt; tag') . '</li>';
      $output .= '</ul>';
      $output .= '</li>';
      $output .= '<li>';
      $output .= t('child_attributes - class and other attributes that will be applied to &lt;li&gt; tags that have no children');
      $output .= '<ul>';
      $output .= '<li>' . t('class - A class to add to the LI so that it can be styled') . '</li>';
      $output .= '<li>' . t("four_corners -> If isset it'll will apply four span's to the parent, the four spans will be called") . '</li>';
      $output .= '<li>' . t('span - if isset, it will apply a span inside the &lt;a&gt; tag') . '</li>';
      $output .= '</ul>';
      $output .= '</li>';
      $output .= '</ul>';
      break;
  }
  return!empty($output) ? $output : '';
}

/**
 * Returns a themed menu. See module's help page for details.
 */
function theme_menu_links_enhanced($variables) {

  // begin with the default values and merge the user-inputted ones onto it
  $attributes = $variables['attributes'];
  $attributes['list_attributes'] = array_merge(menu_enhancement_get_defaults(), $attributes['list_attributes']);

  $tree = $variables['tree'];

  if (!isset($attributes['root'])) {
    $attributes['root'] = TRUE;
  }
  else{
    $attributes['root'] = FALSE;
  }

  if (!isset($attributes['level_counter'])) {
    $attributes['level_counter'] = 0;
  }

  $level = $attributes['list_attributes']['level'];
  $parents = array();
  // Go down the active trail until the right level is reached.
  while ($level-- > 0 && $tree) {
    // Loop through the current level's items until we find one that is in trail.
    while ($item = array_shift($tree)) {
      if ($item['link']['in_active_trail']) {
        if ($item['link']['has_children'] > 0 && $attributes['list_attributes']['show-parents'] !== FALSE && $level >= ($attributes['list_attributes']['level'] - $attributes['list_attributes']['show-parents'])) {
          $parents[] = $item;
        }
        // If the item is in the active trail, we continue in the subtree.
        $tree = empty($item['below']) ? array() : $item['below'];
        break;
      }
    }
  }
  $attributes['list_attributes']['level'] = 0;

  $items = array();
  global $language;
  // Pull out just the menu items we are going to render so that we get an accurate count for the first/last classes.
  foreach ($tree as $data) {
    if (arg(0) == 'admin' && module_exists('translation')) {
      $nid = substr($data['link']['link_path'], 5);
      $node = node_load($nid);
      if (isset($data['link']['hidden']) && !$data['link']['hidden']) {
        if ($node->language == $language->language) {
          $items[] = $data;
        }
      }
      if ($data['link']['link_path'] == 'user/logout' || $data['link']['link_path'] == 'sitemap') {
      $items[] = $data;
      }
    }
    else{
      if (isset($data['link']['hidden'])) {
          if (!$data['link']['hidden']) {
          $items[] = $data;
          }
      }
    }
  }

  $output = '';
  $level_count = $attributes['level_counter'];
  // Render the menu
  $num_items = count($items);
  if ($num_items > 0) {
    $last = FALSE;
    foreach ($items as $i => $data) {
      $menu_item_class = array();
      if ($i == 0) {
        $menu_item_class[] = 'first';
      }
      if ($i == $num_items - 1) {
        $menu_item_class[] = 'last';
        $last = TRUE;
      }

      // Get the english version of the menu item so that the menu class can be the same across languages
      if (module_exists('translation') && $data['link']['router_path'] == 'node/%') {
        $nid = substr($data['link']['link_path'], 5);
        $menu_node = node_load($nid);
        if (isset($menu_node->tnid)) {
          $node_translations = translation_node_get_translations($menu_node->tnid);
          if (isset($node_translations['en'])) {
            $english_menu = menu_enhancement_menu_link(NULL, 'node/' . $node_translations['en']->nid);
          }
        }
      }

      $link_variables['data'] = $data;
      $link_variables['attributes'] = $attributes;

      $link = theme('menu_item_enhanced_link', $link_variables);
      //if english menu isset, use english title else use datalink title
      $menu_item_class[] = isset($english_menu) ? str_replace(' ', '_', "li" . $english_menu['title']) : str_replace(' ', '_', "li" . $data['link']['link_title']);

      $attributes_array = array();

      $attributes['level-count'] = $level_count;

      //if children exist in the data item, call this function again passing in children and attributes
      if ($data['link']['has_children'] == 0) {
        $child_output = $data['below'] && $attributes['list_attributes']['show-children'] ? theme_menu_links_enhanced(array('tree' => $data['below'], 'attributes' => $attributes)) : '';

        if (isset($attributes['child_attributes'])) {
          $attributes_array = menu_enhancement_remove_attributes($attributes, $menu_item_class, FALSE);
        }
      }
      elseif ($data['link']['has_children'] == 1) {
        $level_count++;
        $child_output = $data['below'] && $attributes['list_attributes']['show-children'] ? theme_menu_links_enhanced(array('tree' => $data['below'], 'attributes' => $attributes)) : '';
          if (isset($attributes['parent_attributes'])) {
            $attributes_array = menu_enhancement_remove_attributes($attributes, $menu_item_class, TRUE);
          }
        $level_count--;
      }

      if (count($attributes_array) == 0) {
        $attributes_array = $menu_item_class;
      }

      $extra_class = implode(' ', $attributes_array);

      $in_active_trail = $data['link']['in_active_trail'];
      //if the menu item is a vocabulary term
      /*if ($data['link']['router_path'] == 'catalog') {
        $nid = arg(1);
        if (is_numeric($nid)) {
          $node = node_load($nid);
          if ($node && $node->type == 'product') {
            $in_active_trail = _menu_enhancement_catalog_check_node_active($data['link'], $node);
          }
          elseif (strpos($_GET['q'], 'catalog') !== FALSE) {
            $term_id = arg(1);
            $term = taxonomy_term_load($term_id);
            if ($term) {
              $in_active_trail = _menu_enhancement_catalog_check_term_active($data['link'], $term);
            }
          }
        }
      }*/

      $output .= theme('menu_item_enhanced', array('link' => $link, 'has_children' => $data['link']['has_children'], 'menu' => $child_output, 'in_active_trail' => $in_active_trail, 'extra_class' => $extra_class, 'attributes' => $attributes, 'last' => $last));

      unset($english_menu);
    }

    if ($attributes['root'] == TRUE) {
      $level_count = 0;
    }

    $ul_classname = isset($attributes['list_attributes']['class']) ? $attributes['list_attributes']['class'] : '';
    $ul_class = 'level' . $level_count;

    if (!empty($ul_classname)) {
      $ul_class .= ' ' . $ul_classname;
    }

    if ($attributes['root'] == TRUE) {
      $ul_id = isset($attributes['list_attributes']['id']) ? $attributes['list_attributes']['id'] : '';
    }
    else {
      $ul_id = '';
    }
    $output = count($parents) ? theme('menu_tree_enhanced', array('tree' => $output)) : theme('menu_tree_enhanced', array('tree' => $output, 'attributes' => array('class' => $ul_class, 'id' => $ul_id)));

  }
  // Render the parents at the top of the list
  $parent_level = count($parents);

  while ($parent_level-- > 0) {

    $parent = $parents[$parent_level];

    $link_variables['data'] = $data;
    $link_variables['attributes'] = $attributes;

    $menu_item_class = array('parent');
    $extra_class = implode(' ', $menu_item_class);

    $link = theme('menu_item_enhanced_link', $link_variables);
    $output = theme('menu_item_enhanced', array('link' => $link, 'has_children' => $data['link']['has_children'], 'menu' => $output, 'in_active_trail' => $data['link']['in_active_trail'], 'extra_class' => $extra_class));

    $output = $parent_level > 0 ? theme('menu_tree_enhanced', array('tree' => $output)) : theme('menu_tree_enhanced', array('tree' => $output, 'attributes' => array('id' => $attributes['list_attributes']['id'], 'class' => $attributes['list_attributes']['class'])));
  }

  return $output;
}

//theme function to output the link
//if span attribute is TRUE, the span is outputted between the a tags
function theme_menu_enhancement_link($variables) {

  $link = $variables['data']['link'];
  $data = $variables['data'];

  if (isset($variables['attributes'])) {
    $attributes = $variables['attributes'];
  }

  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }

  $link['localized_options'] = array('html' => TRUE, 'attributes' => array('class' => array(strtolower(str_replace(' ', '_', $link['title'])))));

  $link_title = $link['title'];

  //if span attribute is passed in
  if (($data['link']['has_children'] == 0 && isset($attributes['child_attributes']['span'])) || ($data['link']['has_children'] == 1 && isset($attributes['parent_attributes']['span']))) {
    $link_title = '<span>' . $link['title'] . '</span>';
  }
  $link['localized_options']['attributes']['class'] = str_replace('&', '', $link['localized_options']['attributes']['class']);
  $output = l($link_title, $link['href'], $link['localized_options']);

  return $output;
}

//themes the LI element
//if four corners isset, outputs four spans inside the LI
function theme_menu_enhancement_item($variables) {
  $first = '';

  $span_class_names = array(0 => 'topLeftCorner', 1 => 'top_RightCorner', 2 => 'bottomLeftCorner', 3 => 'bottomRightCorner');

  $class = ($variables['menu'] ? 'expanded' : ($variables['has_children'] ? 'collapsed' : 'leaf'));
  $id_class = '';

  if (!empty($variables['extra_class'])) {
    $f_pos = strpos($variables['extra_class'], 'first');
    if ($f_pos !== FALSE) {
      $first = substr($variables['extra_class'], $f_pos, 5);//go for six cause of the extra space
      $variables['extra_class'] = str_replace('first ', '', $variables['extra_class']);
    }

    $l_pos = strpos($variables['extra_class'], 'last');
    if ($l_pos !== FALSE) {
      $variables['last'] = substr($variables['extra_class'], $l_pos, 4);//go for 5, cause of the extra space
      $variables['extra_class'] = str_replace('last ', '', $variables['extra_class']);
    }
    $id_class = trim($variables['extra_class']);
  }

  if ($variables['in_active_trail']) {
    $class .= ' active-trail';
  }


  ($first != "") ? $class .= ' ' . $first : ''; //if first exists, append it to the class
  ($variables['last'] != "") ? $class .= ' ' . $variables['last'] : '';

  $characters = array('&', ',');
  $class = strtolower(str_replace($characters, '', $class)); //remove &
  $id_class = strtolower(str_replace($characters, '', $id_class)); //remove &

  $id_class = str_replace(' ', '_', $id_class);

  $output = '<li id="' . preg_replace("([^A-Z0-9_]+)i", "", $id_class) . '" class="' . preg_replace("([^A-Z0-9 ]+)i", "", $class) . '">';
  //if it has no children and child four corners isset, use it, OR if it has children and parent four corners isset

  if (($variables['has_children'] == 0 && $variables['attributes']['child_attributes']['four_corners'] > 0) || ($variables['has_children'] == 1 && $variables['attributes']['parent_attributes']['four_corners'] > 0)) {
    for ($i = 0; $i < 4; $i++) {
      $output .= '<span class="' . $span_class_names[$i] . '">';
    }
  }
  $output .= $variables['link'] . $variables['menu'];
  if (($variables['has_children'] == 0 && $variables['attributes']['child_attributes']['four_corners'] > 0) || ($variables['has_children'] == 1 && $variables['attributes']['parent_attributes']['four_corners'] > 0)) {
    for ($i = 0; $i < 4; $i++) {
      $output .= '</span>';
    }
  }

  if (isset($variables['attributes']['list_attributes']['separator']) && $variables['attributes']['list_attributes']['separator'] != NULL && $variables['last'] == FALSE) {
    $output .= ' ' . htmlspecialchars($variables['attributes']['list_attributes']['separator'], ENT_QUOTES, 'UTF-8', FALSE);
  }

  $output .= "</li>\n";

  return $output;
}

//themes the UL elemnt
function menu_enhancement_theme_menu_tree($variables) {
  if ($variables['attributes']['id'] == NULL) {
    unset($variables['attributes']['id']);
  }
  return '<ul' . drupal_attributes($variables['attributes']) . '>' . $variables['tree'] . '</ul>';
}
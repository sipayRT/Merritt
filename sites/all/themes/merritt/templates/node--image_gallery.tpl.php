<?php
// $Id: node.tpl.php,v 1.2 2010/12/01 00:18:15 webchick Exp $

/**
 * @file
 * Bartik's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */


// Teaser View
if(!$page) {

?>

<article class="gallery-item">
  <a href="<?php print $node_url; ?>">
    <span class="gallery-item-image">
      <?php
      if(!empty($node->field_teaser_image[$node->language][0]['uri'])) {
        print theme('image_style', array('style_name' => 'portfolio', 'path' => $node->field_teaser_image[$node->language][0]['uri'], 'alt' => $node->title));
      }
      else {
        print theme('image_style', array('style_name' => 'portfolio', 'path' => $node->field_gallery_image[$node->language][0]['uri'], 'alt' => $node->title));
      }
      ?>
    </span>
    <span class="gallery-item-title"><?php print $title; ?></span>
    <?php
    if(!empty($node->field_teaser_text[$node->language][0]['value'])) {
      print '<span class="gallery-item-teaser">' . $node->field_teaser_text[$node->language][0]['value'] . '</span>';
    }
    ?>
  </a>
</article>


<?php

}

// Node View
else {

?>

<!-- Image Gallery -->
<div id="image-gallery-cont">

  <!-- Image Gallery - Main Image -->
  <div id="image-gallery-main-image-cont">
    <a title="Next" id="b-image-gallery-next" class="b-img" style="display: none;"></a>
    <a title="Previous" id="b-image-gallery-prev" class="b-img" style="display: none;"></a>

    <?php

    foreach($node->field_gallery_image[$node->language] as $key=>$value) {

      print '<div class="image-gallery-main-image-item">';
        print '<div class="image-gallery-main-image-content">';

          if(!empty($value['title'])) {
            print '<div class="image-gallery-main-image-info">';
              print '<p>' . $value['title'] . '</p>';
            print '</div>';
          }

          print theme('image_style', array('style_name' => 'image_gallery', 'path' => $value['uri'], 'alt' => $node->title));
        print '</div>';
      print '</div>';

    }

    ?>
  </div>
  <!-- / Image Gallery - Main Image -->

  <!-- Image Gallery - Navigation -->
  <div id="image-gallery-nav-cont">
    <a id="b-image-gallery-nav-prev" class="b-img" title="Previous"></a>
    <a id="b-image-gallery-nav-next" class="b-img" title="Next"></a>

    <div id="image-gallery-nav-items">
      <ul id="image-gallery-nav">
        <?php
        // Image Gallery - Thumbnails
        foreach($node->field_gallery_image[$node->language] as $key=>$value) {
          print '<li>';
            print '<a href="#">';
              print theme('image_style', array('style_name' => 'image_gallery_thumb', 'path' => $value['uri'], 'alt' => $node->title));
            print '</a>';
          print '</li>';
        }
        ?>
      </ul>
    </div>
  </div>
  <!-- / Image Gallery - Navigation -->

</div>
<!-- / Image Gallery -->

<?php print render($content); ?>

<div class="clear-both"></div>

<p><a href="<?php print base_path(); ?>portfolio">&laquo; Back to Portfolio</a></p>

<?php } ?>

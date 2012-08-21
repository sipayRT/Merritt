<?php
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

$i = 0;
$row_total = count($rows);

?>
<?php foreach ($rows as $id => $row): ?>

  <?php
    $i++;

    if(($i % 3) == 0) {
      $last_class = ' last_in_row';
    }
    else {
      $last_class = '';
    }
  ?>

  <div class="<?php print $classes_array[$id] . $last_class; ?>">
    <?php print $row; ?>
  </div>
  <?php if(($i % 3) == 0) { print '<div class="clear-both"></div>'; } ?>
<?php endforeach; ?>
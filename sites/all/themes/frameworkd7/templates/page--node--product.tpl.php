<?php
// $Id: page.tpl.php,v 1.47 2010/11/05 01:25:33 dries Exp $

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

    <!-- site wrapper -->
    <div id="site-wrapper" class="page-content">

      <!-- site container -->
      <div id="site-container">

        <!-- site header -->
        <?php include_once('site_header.inc'); ?>
        <!-- / site header -->

        <!-- primary navigation -->
        <div id="pri-nav-cont">
          <?php print $primary_navigation; ?>
          <div id="header-layout-switcher">
            <ul id="layout-switcher">
              <li id="ls-a"><a href="/">A</a></li>
              <li id="ls-b"><a href="/home-layout-b">B</a></li>
              <li id="ls-c"><a href="/home-layout-c">C</a></li>
            </ul>
          </div>
        </div>
        <!-- / primary navigation -->

        <!-- site content -->
        <div id="site-content" <?php if(!empty($page_layout_css)) { print 'class="' . $page_layout_css . '"'; } ?>>

          <!-- left column -->
          <div id="site-left-col">
            <div id="site-left-col-content">

              <!-- catalog navigation -->
              <div id="sec-nav-cont">
              	<h2 class="sec-nav-header"><?php print l(t('Products'), 'products'); ?></h2>
                <?php print commerce_custom_menu_out(); ?>
              </div>
              <!-- / catalog navigation -->

              <?php print views_embed_view('ctas', 'block'); ?>

            </div>
          </div>
          <!-- / left column -->

          <!-- main body content -->
          <div id="site-main-cont">
            <div class="site-main-content">
              <?php if ($tabs['#primary']){ ?><div class="tabs"><?php print render($tabs); ?></div><br class="clear-both" /><?php } ?>
              <?php print $messages; ?>
              <?php if ($action_links){ ?><ul class="action-links"><?php print render($action_links); ?></ul><?php } ?>
              <div id="product-content">
                <?php print render($page['content']); ?>
                <div class="clear-both"></div>
              </div>
            </div>
          </div>
          <!-- / main body content -->

          <div class="clear-both"></div>

        </div>
        <!-- / site content -->

      </div>
      <!-- / site container -->

    </div>
    <!-- / site wrapper -->

    <!-- site footer -->
    <?php include_once('site_footer.inc'); ?>
    <!-- / site footer -->

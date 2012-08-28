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
drupal_add_css($directory . '/css/style_nivo-slider.css', array('group' => CSS_THEME, 'every_page' => FALSE));
drupal_add_js($directory . '/js/jquery.nivo.slider.pack.js', 'file');
?>

    <!-- site header -->
    <?php include_once('site_header.inc'); ?>
    <!-- / site header -->
	
    <!-- site wrapper -->
    <div id="site-wrapper">

		<!-- site container -->
		<div id="site-container">
			<!-- site content wrapper -->
			<div id="site-content-wrapper">
			
				<!-- site content -->
				<div id="site-content">
				  <div id="col-left">
				    <div class="add-pad">
						<?php if ($title){ ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php } ?>
						<?php if ($tabs['#primary']){ ?><div class="tabs"><?php print render($tabs); ?></div><br class="clear-both" /><?php } ?>
						<?php print $messages; ?>
						<?php if ($action_links){ ?><ul class="action-links"><?php print render($action_links); ?></ul><?php } ?>
						<div id="user-content">
							<?php print render($page['content']); ?>
						</div>
					</div>
				  </div>
				  <div id="col-right">
				    <div class="add-pad">
						<section id="sidebar">
				        	<?php if ($page['sidebar']): ?>
				                <?php print render($page['sidebar']); ?>
				    		<?php endif; ?>
				      	</section>
				    </div>
				  </div>
				  <div class="clear-both"></div>
				</div>																						
				<!-- / site content -->
				
			</div>
			<!-- / site content wrapper -->

			<?php if ($page['footer_3_blocks']): ?>
			    <div class="footer-three-blocks">
			        <?php print render($page['footer_3_blocks']); ?>
			    </div>
			<?php endif; ?>
			
		</div>
		<!-- / site container -->

    </div>
    <!-- / site wrapper -->

    <!-- site footer -->
    <?php include_once('site_footer.inc'); ?>
    <!-- / site footer -->
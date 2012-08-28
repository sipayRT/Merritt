<header>
	<div class="header-wrapper">
		<div id="site-header-left">
			<h1 id="site-logo">
				<a href="<?php print $front_page; ?>" title="<?php print t($site_name); ?>" rel="home"><img src="/<?php print path_to_theme(); ?>/gfx/site_logo.png" alt="<?php print t($site_name); ?>" /></a>
			</h1>
		</div>
		<div id="site-header-right">
            <?php if ($page['header_menu']): ?>
                <div class="header-menu">
                    <?php print render($page['header_menu']); ?>
                </div>
            <?php endif; ?>
            <?php if ($page['header_widgets']): ?>
                <div class="header-widgets">
                    <?php print render($page['header_widgets']); ?>
                </div>
            <?php endif; ?>
		</div>
		<br class="clear-both" />
	</div>
	<!-- primary navigation -->
	<div class="header-menu-wrapper">
        <?php if ($page['main_content_menu']): ?>
            <div id="pri-nav-cont">
                <?php print render($page['main_content_menu']); ?>
            </div>
        <?php endif; ?>
	</div>
	<!-- / primary navigation -->
	<!-- fixed navigation -->
	<div class="fixed-menu-wrapper">
        <?php if ($page['fixed_menu']): ?>
            <div id="fixed-nav-cont">
                <?php print render($page['fixed_menu']); ?>
				<div class="fixed-menu-button">I want to...</div>
            </div>
        <?php endif; ?>
	</div>
	<!-- / fixed navigation -->
</header>

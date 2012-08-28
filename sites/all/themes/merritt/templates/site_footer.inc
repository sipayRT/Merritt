		<footer>
			<div id="site-footer">
				<div id="ft-bot">
					<div id="sm-nav-cont">
						<?php print $social_media_navigation; ?>
					</div>
					<br class="clear-both" />
				</div>
				<div id="footer-text">
					<div id="ft-copy">
						Copyright &copy; <?php print date('Y'); ?> <a href="/">Acro Media Inc.</a>. All rights reserved.
						<?php print render($page['footer_text']); ?>
					</div>
					<div id="footer-nav-cont">
						<?php print $footer_navigation; ?>
					</div>
					<br class="clear-both" />
				</div>
			</div>
		</footer>

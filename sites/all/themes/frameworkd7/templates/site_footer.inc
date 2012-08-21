		<footer>
			<div id="site-footer">
				<div id="ft-top">
					<div class="add-pad">
						<div id="newsletter-signup-form">
							<?php print render($page['newsletter_signup_form']); ?>
						</div>
						<div id="search-form">
							<?php print render($page['search_form']); ?>
						</div>
						<br class="clear-both" />
					</div>
				</div>
				<div id="ft-bot">
					<div class="add-pad">
						<div id="sm-nav-cont">
							<?php print $social_media_navigation; ?>
						</div>
						<div id="footer-nav-cont">
							<?php print $footer_navigation; ?>
						</div>
						<br class="clear-both" />
					</div>
				</div>
				<div id="footer-text">
					<p id="ft-copy">Copyright &copy; <?php print date('Y'); ?> <a href="/">Acro Media Inc.</a>. All rights reserved.</p>
					<?php print render($page['footer_text']); ?>
					<br class="clear-both" />
				</div>
			</div>
		</footer>

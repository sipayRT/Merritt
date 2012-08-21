        <header>
          <div id="site-header-left">
            <h1 id="site-logo">
              <a href="<?php print $front_page; ?>" title="<?php print t($site_name); ?>" rel="home"><img src="/<?php print path_to_theme(); ?>/gfx/site_logo.png" alt="<?php print t($site_name); ?>" /></a>
            </h1>
          </div>
          <div id="site-header-right">
            <div id="site-header-contact">
              <p><?php print variable_get('contact_header_text', NULL); ?><a href="<?php print variable_get('contact_link', NULL); ?>"><?php print variable_get('contact_header_phone', NULL); ?></a></p>
              <p>E-mail: <a href="mailto:<?php print variable_get('contact_header_email', NULL); ?>"><?php print variable_get('contact_header_email', NULL); ?></a></p>
            </div>
          </div>
          <br class="clear-both" />
        </header>

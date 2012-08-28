/**
 *	author: copyright (c) 1998-2012 Acro Media Inc.
 *	purpose: JS for Personal Strengths
 */
var $ = jQuery;

$(function() {

  /* -- Homepage Rich Media -- */
  if($('.nivoSlider').length) {
    $('.nivoSlider').nivoSlider({
      pauseTime: 6000,
      effect: 'random',
      directionNav: true,
      controlNav: true,
      pauseOnHover: false,
      directionNavHide: true
    });
  }

  /* -- Default Text For Forms -- */

  // sign up form
  $("#webform-client-form-21 #edit-submitted-name.required").defaultValue("Your Name (Required)");

  // This is the ID of the footer newsletter when on the actual newsletter page
  $("#webform-client-form-21--2 #edit-submitted-name--2").defaultValue("Your Name (Required)");

  // search form
  $('#search-block-form .form-text').defaultValue("Search Site");

  /* -- Image Gallery -- */
  if($('#image-gallery-cont').length) {

    // Display next and prev buttons on hover
    $('#image-gallery-main-image-cont').hover(
      function () {
        $('#b-image-gallery-next, #b-image-gallery-prev').stop(true, true);
        $('#b-image-gallery-next, #b-image-gallery-prev').fadeIn();
      },
      function () {
        $('#b-image-gallery-next, #b-image-gallery-prev').fadeOut();
      }
    );

    // Hover State For Description
    if($('.image-gallery-main-image-info').length) {
      $('.image-gallery-main-image-item').hover(
        function () {
          $(this).find('.image-gallery-main-image-info').stop(true, true);
          $(this).find('.image-gallery-main-image-info').fadeIn()
        },
        function () {
          $(this).find('.image-gallery-main-image-info').fadeOut()
        }
      );
    }

    // Image Gallery - Define Number Of Visual Thumbnails
    var imageGalleryNumbOfThumbs = 4;

    // Get length of thumbnail items
    var imageGalleryThumbLength = $('#image-gallery-nav li').length;

    // Add class for no scrollbars if there's not enough thumbnails to scroll through
    if(imageGalleryThumbLength <= imageGalleryNumbOfThumbs) {
      $('#image-gallery-nav-cont').addClass('no_scroller');
    }
    // Image Gallery - Setup Scrollable Nav
    $("#image-gallery-nav-items").scrollable({ speed: 300 });

    var imageGalleryScroller = $("#image-gallery-nav-items").data("scrollable");

    var numberOfItems = imageGalleryScroller.getSize();
    var scrollMax = numberOfItems - imageGalleryNumbOfThumbs;

    // Image Gallery - Next Button
    $('#b-image-gallery-nav-next, #b-image-gallery-next').click(function() {
      var currentIndex = imageGalleryScroller.getIndex();

      if(scrollMax != currentIndex && numberOfItems > imageGalleryNumbOfThumbs) {
       imageGalleryScroller.next();
      }

      checkScrolling();
      return false;
    });

    // Image Gallery - Prev Button
    $('#b-image-gallery-nav-prev, #b-image-gallery-prev').click(function() {
      imageGalleryScroller.prev();
      checkScrolling();
      return false;
    });

    // Check whether to disable next/prev buttons
    function checkScrolling() {
      var available_scroll_index = numberOfItems - imageGalleryNumbOfThumbs;

      // Check next button
      if(imageGalleryScroller.getIndex() >= available_scroll_index) {
        $('#b-image-gallery-nav-next').addClass('disabled');
      } else if(imageGalleryScroller.getIndex() <= available_scroll_index) {
        $('#b-image-gallery-nav-next').removeClass('disabled');
      }

      // Check previous button
      if(imageGalleryScroller.getIndex() != 0) {
        $('#b-image-gallery-nav-prev').removeClass('disabled');
      } else {
        $('#b-image-gallery-nav-prev').addClass('disabled');
      }

    }

    // Run the scroller check
    checkScrolling();

    // Image Gallery - Setup Tabs
    $("#image-gallery-nav").tabs("#image-gallery-main-image-cont > .image-gallery-main-image-item", {
      effect: 'fade',
      fadeOutSpeed: "slow",
      rotate: true
      });

    var imageGalleryNavAPI = $("#image-gallery-nav").data("tabs");

    // Image Gallery - Large Next Button
    $('#b-image-gallery-next').click(function() {
      var tabLimit = numberOfItems - 1;
      var currentTabIndex = imageGalleryNavAPI.getIndex();

      // Scroll to the beginning after reaching the end
      if(currentTabIndex == tabLimit) {
        imageGalleryScroller.begin();
      }

      checkScrolling();
      imageGalleryNavAPI.next();
    });

    // Image Gallery - Large Prev Button
    $('#b-image-gallery-prev').click(function() {
      var tabLimit = numberOfItems - 1;
      var currentTabIndex = imageGalleryNavAPI.getIndex();

      // Scroll to the beginning after reaching the end
      if(currentTabIndex == 0 & numberOfItems > imageGalleryNumbOfThumbs) {
        imageGalleryScroller.seekTo(tabLimit);
      }

      checkScrolling();
      imageGalleryNavAPI.prev();
    });
  };

});

/**
 * binds jQuery functions to a number of elements to create elements that will slide open and closed
 * when a button is clicked
 *
 * elements should be built like the following:
 *
 * <div class="containerClass">
 *   <div class="buttonClass"></div>
 *   <div class="slideClass"></div>
 * </div>
 *
 * @param {String} containerClass
 *   the CSS class name of the elements that contain buttonClass and slideClass
 * @param {String} buttonClass
 *   the CSS class name of the button that should slide slideClass when clicked
 * @param {String} slideClass
 *   the CSS class name of the element that should open and closed when buttonClass is clicked
 */
function slideToggle(containerClass, buttonClass, slideClass) {
  $(containerClass).each(function() {
    $(this).find(buttonClass).click(function() {
      $(this).parent().find(slideClass).toggle("normal");
      var $this = $(this);
      if($(this).is(".open") ) {
        $this.removeClass("open");
      }
      else {
        $this.addClass("open");
      }
      return false;
    });
  });
}

/**
 * gets the parameters from the current URL and places them in an array
 *
 * @return
 *   an array containing key and value pairs of the URL parameters
 */
function getUrlVariables() {
  var vars = {};
  var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
    vars[key] = value;
  });
  return vars;
}

/**
 * adjust navigation so that each menu item has the
 * appropriate padding to fill out
 */
function adjustNav(element, parentElement) {
  var itemCount = $(element).children('li').size();
  var menuWidth = $(parentElement + element).width();
  var newMenuWidth = 940 - menuWidth;
  newMenuWidth = newMenuWidth / itemCount;
  var paddingString = '0px ' + Math.floor(newMenuWidth/2) + 'px 0px ' + Math.floor(newMenuWidth/2) + 'px';
  $(parentElement + element).children('li').children('a').css('padding', paddingString);
}

/// default input text
jQuery.fn.defaultValue = function(text){
    return this.each(function(){
    //Make sure we're dealing with text-based form fields
    if(this.type != 'text' && this.type != 'password' && this.type != 'textarea')
      return;

    //Store field reference
    var fld_current=this;

    //Set value initially if none are specified
        if(this.value=='' || this.value == text) {
      this.value=text;
    } else {
      //Other value exists - ignore
      return;
    }

    //Remove values on focus
    $(this).focus(function() {
      if(this.value==text || this.value=='')
        this.value='';
    });

    //Place values back on blur
    $(this).blur(function() {
      if(this.value==text || this.value=='')
        this.value=text;
    });

    //Capture parent form submission
    //Remove field values that are still default
    $(this).parents("form").each(function() {
      //Bind parent form submit
      $(this).submit(function() {
        if(fld_current.value==text) {
          fld_current.value='';
        }
      });
    });
  });
};
(function($){
Drupal.behaviors.custom = { attach: function (context, settings) {
	//Show/Hide search field
	$('.search-icon').click(function() {
		if($(this).parent().find('.search-wrapper').hasClass('show')){
			$(this).parent().find('.search-wrapper').removeClass("show").slideUp();
		}else{
			$(this).parent().find('.search-wrapper').addClass("show").slideDown();
		}
		
	});
	$('.search-wrapper #edit-submit').val('GO');
	
	
	//Menu "I want to.."
	
	$('.region-fixed-menu .block-menu ul.menu li.expanded a').each(function(){
		$(this).addClass('convolute');
		$(this).parent().removeClass('expanded');
		$(this).next().hide();
	});
	
	
	//Show menu "I want to.."
	 $(".fixed-menu-button", context).toggle(function(){
        $(".region-fixed-menu .block-menu").animate({"left": "+=192px"}, "slow");
        
		//extanded menu 
		$('.region-fixed-menu .block-menu ul.menu a.convolute', context).toggle(function(){
			$(this).toggleClass("convolute"); 
			$(this).toggleClass("expanded");  
			$(this).next().slideDown();
			return false;
		},function(){
			$(this).toggleClass("expanded");  
			$(this).toggleClass("convolute");
			$(this).next().slideUp();
			return false;
		});  
		$(this).html("close");
		return false;
    },function(){
		  $('.region-fixed-menu .block-menu ul.menu a.expanded', context).each(function(){
			$(this).addClass('convolute');
			$(this).removeClass('expanded');
			$(this).next().slideUp();
		});  
        $(".region-fixed-menu .block-menu").animate({"left": "-=192px"}, "slow");
      //  $(this).toggleClass("active");  $("#block-menu-menu-i-want-to").animate({"width": "-=230px",opacity: "hide"}, "slow");
		$(this).html("I want to ...");
		
		return false;
    });  
	
	
	
	
}};	
})(jQuery);

/**
 * Google Timeline javascript
 *
 */

// Load the Visualization API and the chart package.


(function($) {
  Drupal.behaviors.googleChart = {
    attach: function(context, settings) {
      console.log(settings.google_timeline["nid1075"]); 
    }
  };
})(jQuery);


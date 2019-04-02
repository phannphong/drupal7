/**
 * @file
 * Contains the definition of the behaviour artistics.
 */

(function ($, Drupal) {

    'use strict';
  
    Drupal.behaviors.drupal7_theme = {
      attach: function (context, settings) {
        
        $('ul > li.first.leaf').on('click', function(e) {
            $('#phannphong').load('/node/get/ajax/19381');
            e.preventDefault();
        });

        $('form input.webform-submit').once().click(function() {
          console.log('test');
          $('#phannphong').append('test_');
        });
      }
  
    };
  
    $(document).ready(function(context) {
      $('body').on('submit', function(e) {
        $('form').find('.messages.error').remove();
        var $recaptchaResponse = $('body').find('#g-recaptcha-response');

        if ($recaptchaResponse.length && $recaptchaResponse.val() == "") {
          var htmlError = '<div class="messages error">The recaptcha.</div>';
          $('form').prepend(htmlError);
          $('<span class="red recaptcha">reCAPTCHA is invalid</span>').insertAfter('.g-recaptcha');
          e.preventDefault();
        } else {
          var phone = '';
          var testPhone = /^\d+$/;
          var $phoneInput = $(this).find('.webform-component--phone > input');

          if ($phoneInput.length) {
            phone = $phoneInput.val();
          }
          if (testPhone.test(phone)) {
          }
          else {
            console.log('test');
            var htmlError = '<div class="messages error">' + Drupal.t('The telephone number should only contain numbers. Please correct.') + '</div>';
            $('form').prepend(htmlError);
            e.preventDefault();
          }
        }

      })
    });
  
  })(jQuery, Drupal);
  
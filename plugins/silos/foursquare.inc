<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Foursquare App
 * @see https://foursquare.com/developers/apps
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Foursquare',
  'class' => 'FoursquareSilo',
);

/**
 * Class FoursquareSilo.
 */
class FoursquareSilo extends Silo {

  protected $title = 'Foursquare';

  protected $scopes = array();

  public function authenticate() {
    parent::authenticate();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch (Exception $e) {
      if (!empty($_GET['code'])) {
        // This was a callback request from remote, get the token.
        $this->service->requestAccessToken($_GET['code']);
      }
      else {
        $url = $this->service->getAuthorizationUri();
        header('Location: ' . $url);
      }
    }
  }

}

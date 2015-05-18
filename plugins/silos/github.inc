<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a GitHub App
 * @see https://github.com/settings/developers
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'GitHub',
  'class' => 'GithubSilo',
);

/**
 * Class GithubSilo.
 */
class GithubSilo extends Silo {

  protected $title = 'GitHub';

  protected $scopes = array('user', 'repo');

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
